#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct wilc_sdio {int has_thrpt_enh3; int /*<<< orphan*/  block_size; int /*<<< orphan*/  irq_gpio; } ;
struct wilc {int /*<<< orphan*/  dev_irq_num; struct wilc_sdio* bus_data; int /*<<< orphan*/  dev; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct sdio_cmd52 {int read_write; int raw; int address; int data; scalar_t__ function; } ;

/* Variables and functions */
 int /*<<< orphan*/  WILC_SDIO_BLOCK_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 struct sdio_func* dev_to_sdio_func (int /*<<< orphan*/ ) ; 
 int wilc_sdio_cmd52 (struct wilc*,struct sdio_cmd52*) ; 
 int /*<<< orphan*/  wilc_sdio_read_reg (struct wilc*,int,int*) ; 
 int /*<<< orphan*/  wilc_sdio_set_func0_block_size (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wilc_sdio_set_func1_block_size (struct wilc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wilc_sdio_init(struct wilc *wilc, bool resume)
{
	struct sdio_func *func = dev_to_sdio_func(wilc->dev);
	struct wilc_sdio *sdio_priv = wilc->bus_data;
	struct sdio_cmd52 cmd;
	int loop, ret;
	u32 chipid;

	if (!resume)
		sdio_priv->irq_gpio = wilc->dev_irq_num;

	/**
	 *      function 0 csa enable
	 **/
	cmd.read_write = 1;
	cmd.function = 0;
	cmd.raw = 1;
	cmd.address = 0x100;
	cmd.data = 0x80;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	if (ret) {
		dev_err(&func->dev, "Fail cmd 52, enable csa...\n");
		goto fail;
	}

	/**
	 *      function 0 block size
	 **/
	if (!wilc_sdio_set_func0_block_size(wilc, WILC_SDIO_BLOCK_SIZE)) {
		dev_err(&func->dev, "Fail cmd 52, set func 0 block size...\n");
		goto fail;
	}
	sdio_priv->block_size = WILC_SDIO_BLOCK_SIZE;

	/**
	 *      enable func1 IO
	 **/
	cmd.read_write = 1;
	cmd.function = 0;
	cmd.raw = 1;
	cmd.address = 0x2;
	cmd.data = 0x2;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	if (ret) {
		dev_err(&func->dev,
			"Fail cmd 52, set IOE register...\n");
		goto fail;
	}

	/**
	 *      make sure func 1 is up
	 **/
	cmd.read_write = 0;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = 0x3;
	loop = 3;
	do {
		cmd.data = 0;
		ret = wilc_sdio_cmd52(wilc, &cmd);
		if (ret) {
			dev_err(&func->dev,
				"Fail cmd 52, get IOR register...\n");
			goto fail;
		}
		if (cmd.data == 0x2)
			break;
	} while (loop--);

	if (loop <= 0) {
		dev_err(&func->dev, "Fail func 1 is not ready...\n");
		goto fail;
	}

	/**
	 *      func 1 is ready, set func 1 block size
	 **/
	if (!wilc_sdio_set_func1_block_size(wilc, WILC_SDIO_BLOCK_SIZE)) {
		dev_err(&func->dev, "Fail set func 1 block size...\n");
		goto fail;
	}

	/**
	 *      func 1 interrupt enable
	 **/
	cmd.read_write = 1;
	cmd.function = 0;
	cmd.raw = 1;
	cmd.address = 0x4;
	cmd.data = 0x3;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	if (ret) {
		dev_err(&func->dev, "Fail cmd 52, set IEN register...\n");
		goto fail;
	}

	/**
	 *      make sure can read back chip id correctly
	 **/
	if (!resume) {
		if (!wilc_sdio_read_reg(wilc, 0x1000, &chipid)) {
			dev_err(&func->dev, "Fail cmd read chip id...\n");
			goto fail;
		}
		dev_err(&func->dev, "chipid (%08x)\n", chipid);
		if ((chipid & 0xfff) > 0x2a0)
			sdio_priv->has_thrpt_enh3 = 1;
		else
			sdio_priv->has_thrpt_enh3 = 0;
		dev_info(&func->dev, "has_thrpt_enh3 = %d...\n",
			 sdio_priv->has_thrpt_enh3);
	}

	return 1;

fail:

	return 0;
}