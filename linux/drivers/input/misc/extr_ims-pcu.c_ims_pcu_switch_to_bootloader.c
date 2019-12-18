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
struct ims_pcu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JUMP_TO_BTLDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ims_pcu_execute_command (struct ims_pcu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ims_pcu_switch_to_bootloader(struct ims_pcu *pcu)
{
	int error;

	/* Execute jump to the bootoloader */
	error = ims_pcu_execute_command(pcu, JUMP_TO_BTLDR, NULL, 0);
	if (error) {
		dev_err(pcu->dev,
			"Failure when sending JUMP TO BOOLTLOADER command, error: %d\n",
			error);
		return error;
	}

	return 0;
}