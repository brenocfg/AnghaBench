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
struct i40e_pf {int /*<<< orphan*/  state; TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_BAD_EEPROM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int i40e_diag_eeprom_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_verify_eeprom(struct i40e_pf *pf)
{
	int err;

	err = i40e_diag_eeprom_test(&pf->hw);
	if (err) {
		/* retry in case of garbage read */
		err = i40e_diag_eeprom_test(&pf->hw);
		if (err) {
			dev_info(&pf->pdev->dev, "eeprom check failed (%d), Tx/Rx traffic disabled\n",
				 err);
			set_bit(__I40E_BAD_EEPROM, pf->state);
		}
	}

	if (!err && test_bit(__I40E_BAD_EEPROM, pf->state)) {
		dev_info(&pf->pdev->dev, "eeprom check passed, Tx/Rx traffic enabled\n");
		clear_bit(__I40E_BAD_EEPROM, pf->state);
	}
}