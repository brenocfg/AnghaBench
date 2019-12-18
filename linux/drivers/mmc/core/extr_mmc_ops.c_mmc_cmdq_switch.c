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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int cmdq_en; int /*<<< orphan*/  generic_cmd6_time; int /*<<< orphan*/  cmdq_support; } ;
struct mmc_card {TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT_CSD_CMDQ_MODE_EN ; 
 int /*<<< orphan*/  EXT_CSD_CMDQ_MODE_ENABLED ; 
 int /*<<< orphan*/  EXT_CSD_CMD_SET_NORMAL ; 
 int mmc_switch (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_cmdq_switch(struct mmc_card *card, bool enable)
{
	u8 val = enable ? EXT_CSD_CMDQ_MODE_ENABLED : 0;
	int err;

	if (!card->ext_csd.cmdq_support)
		return -EOPNOTSUPP;

	err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_CMDQ_MODE_EN,
			 val, card->ext_csd.generic_cmd6_time);
	if (!err)
		card->ext_csd.cmdq_en = enable;

	return err;
}