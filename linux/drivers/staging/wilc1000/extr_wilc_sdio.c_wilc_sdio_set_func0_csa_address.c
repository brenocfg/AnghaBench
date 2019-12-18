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
typedef  void* u8 ;
typedef  int u32 ;
struct wilc {int /*<<< orphan*/  dev; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct sdio_cmd52 {int read_write; int address; void* data; scalar_t__ raw; scalar_t__ function; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct sdio_func* dev_to_sdio_func (int /*<<< orphan*/ ) ; 
 int wilc_sdio_cmd52 (struct wilc*,struct sdio_cmd52*) ; 

__attribute__((used)) static int wilc_sdio_set_func0_csa_address(struct wilc *wilc, u32 adr)
{
	struct sdio_func *func = dev_to_sdio_func(wilc->dev);
	struct sdio_cmd52 cmd;
	int ret;

	/**
	 *      Review: BIG ENDIAN
	 **/
	cmd.read_write = 1;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = 0x10c;
	cmd.data = (u8)adr;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	if (ret) {
		dev_err(&func->dev, "Failed cmd52, set 0x10c data...\n");
		goto fail;
	}

	cmd.address = 0x10d;
	cmd.data = (u8)(adr >> 8);
	ret = wilc_sdio_cmd52(wilc, &cmd);
	if (ret) {
		dev_err(&func->dev, "Failed cmd52, set 0x10d data...\n");
		goto fail;
	}

	cmd.address = 0x10e;
	cmd.data = (u8)(adr >> 16);
	ret = wilc_sdio_cmd52(wilc, &cmd);
	if (ret) {
		dev_err(&func->dev, "Failed cmd52, set 0x10e data...\n");
		goto fail;
	}

	return 1;
fail:
	return 0;
}