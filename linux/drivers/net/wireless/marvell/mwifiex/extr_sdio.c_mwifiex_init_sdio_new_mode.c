#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sdio_mmc_card {TYPE_1__* reg; } ;
struct mwifiex_adapter {int /*<<< orphan*/  ioport; struct sdio_mmc_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_cfg_1; int /*<<< orphan*/  cmd_cfg_0; int /*<<< orphan*/  card_cfg_2_1_reg; } ;

/* Variables and functions */
 int CMD53_NEW_MODE ; 
 int CMD_PORT_AUTO_EN ; 
 int CMD_PORT_RD_LEN_EN ; 
 int /*<<< orphan*/  MEM_PORT ; 
 scalar_t__ mwifiex_read_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ mwifiex_write_reg (struct mwifiex_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mwifiex_init_sdio_new_mode(struct mwifiex_adapter *adapter)
{
	u8 reg;
	struct sdio_mmc_card *card = adapter->card;

	adapter->ioport = MEM_PORT;

	/* enable sdio new mode */
	if (mwifiex_read_reg(adapter, card->reg->card_cfg_2_1_reg, &reg))
		return -1;
	if (mwifiex_write_reg(adapter, card->reg->card_cfg_2_1_reg,
			      reg | CMD53_NEW_MODE))
		return -1;

	/* Configure cmd port and enable reading rx length from the register */
	if (mwifiex_read_reg(adapter, card->reg->cmd_cfg_0, &reg))
		return -1;
	if (mwifiex_write_reg(adapter, card->reg->cmd_cfg_0,
			      reg | CMD_PORT_RD_LEN_EN))
		return -1;

	/* Enable Dnld/Upld ready auto reset for cmd port after cmd53 is
	 * completed
	 */
	if (mwifiex_read_reg(adapter, card->reg->cmd_cfg_1, &reg))
		return -1;
	if (mwifiex_write_reg(adapter, card->reg->cmd_cfg_1,
			      reg | CMD_PORT_AUTO_EN))
		return -1;

	return 0;
}