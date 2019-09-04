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
typedef  int /*<<< orphan*/  u32 ;
struct hideep_ts {int /*<<< orphan*/  nvm_mask; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDEEP_FLASH_CFG ; 
 int /*<<< orphan*/  HIDEEP_NVM_DEFAULT_PAGE ; 
 int /*<<< orphan*/  HIDEEP_NVM_MASK_OFS ; 
 int /*<<< orphan*/  HIDEEP_NVM_SFR_RPAGE ; 
 int /*<<< orphan*/  HIDEEP_NVM_SFR_WPAGE ; 
 int /*<<< orphan*/  HIDEEP_PROT_MODE ; 
 int /*<<< orphan*/  NVM_W_SFR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FLASH_HWCONTROL () ; 
 int /*<<< orphan*/  SET_FLASH_PIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hideep_pgm_r_reg (struct hideep_ts*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hideep_pgm_w_reg (struct hideep_ts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hideep_nvm_unlock(struct hideep_ts *ts)
{
	u32 unmask_code;

	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_SFR_RPAGE);
	hideep_pgm_r_reg(ts, 0x0000000C, &unmask_code);
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_DEFAULT_PAGE);

	/* make it unprotected code */
	unmask_code &= ~HIDEEP_PROT_MODE;

	/* compare unmask code */
	if (unmask_code != ts->nvm_mask)
		dev_warn(&ts->client->dev,
			 "read mask code different %#08x vs %#08x",
			 unmask_code, ts->nvm_mask);

	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_SFR_WPAGE);
	SET_FLASH_PIO(0);

	NVM_W_SFR(HIDEEP_NVM_MASK_OFS, ts->nvm_mask);
	SET_FLASH_HWCONTROL();
	hideep_pgm_w_reg(ts, HIDEEP_FLASH_CFG, HIDEEP_NVM_DEFAULT_PAGE);
}