#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct isar_hw {int version; TYPE_2__* ch; int /*<<< orphan*/  hw; int /*<<< orphan*/  (* ctrl ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int debug; int /*<<< orphan*/  Flags; } ;
struct TYPE_4__ {TYPE_1__ bch; int /*<<< orphan*/  ftimer; } ;

/* Variables and functions */
 int DEBUG_HW ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLG_INITIALIZED ; 
 int /*<<< orphan*/  HW_RESET_REQ ; 
 int ISARVersion (struct isar_hw*) ; 
 int /*<<< orphan*/  ftimer_handler ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_isar(struct isar_hw *isar)
{
	int	cnt = 3;

	while (cnt--) {
		isar->version = ISARVersion(isar);
		if (isar->ch[0].bch.debug & DEBUG_HW)
			pr_notice("%s: Testing version %d (%d time)\n",
				  isar->name, isar->version, 3 - cnt);
		if (isar->version == 1)
			break;
		isar->ctrl(isar->hw, HW_RESET_REQ, 0);
	}
	if (isar->version != 1)
		return -EINVAL;
	timer_setup(&isar->ch[0].ftimer, ftimer_handler, 0);
	test_and_set_bit(FLG_INITIALIZED, &isar->ch[0].bch.Flags);
	timer_setup(&isar->ch[1].ftimer, ftimer_handler, 0);
	test_and_set_bit(FLG_INITIALIZED, &isar->ch[1].bch.Flags);
	return 0;
}