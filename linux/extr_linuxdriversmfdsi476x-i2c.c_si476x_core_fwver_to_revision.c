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
struct si476x_core {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SI476X_FUNC_AM_RECEIVER 131 
#define  SI476X_FUNC_BOOTLOADER 130 
#define  SI476X_FUNC_FM_RECEIVER 129 
#define  SI476X_FUNC_WB_RECEIVER 128 
 int SI476X_REVISION_A10 ; 
 int SI476X_REVISION_A20 ; 
 int SI476X_REVISION_A30 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int) ; 

__attribute__((used)) static int si476x_core_fwver_to_revision(struct si476x_core *core,
					 int func, int major,
					 int minor1, int minor2)
{
	switch (func) {
	case SI476X_FUNC_FM_RECEIVER:
		switch (major) {
		case 5:
			return SI476X_REVISION_A10;
		case 8:
			return SI476X_REVISION_A20;
		case 10:
			return SI476X_REVISION_A30;
		default:
			goto unknown_revision;
		}
	case SI476X_FUNC_AM_RECEIVER:
		switch (major) {
		case 5:
			return SI476X_REVISION_A10;
		case 7:
			return SI476X_REVISION_A20;
		case 9:
			return SI476X_REVISION_A30;
		default:
			goto unknown_revision;
		}
	case SI476X_FUNC_WB_RECEIVER:
		switch (major) {
		case 3:
			return SI476X_REVISION_A10;
		case 5:
			return SI476X_REVISION_A20;
		case 7:
			return SI476X_REVISION_A30;
		default:
			goto unknown_revision;
		}
	case SI476X_FUNC_BOOTLOADER:
	default:		/* FALLTHROUG */
		BUG();
		return -1;
	}

unknown_revision:
	dev_err(&core->client->dev,
		"Unsupported version of the firmware: %d.%d.%d, "
		"reverting to A10 compatible functions\n",
		major, minor1, minor2);

	return SI476X_REVISION_A10;
}