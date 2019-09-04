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
struct isar_hw {TYPE_2__* ch; } ;
struct TYPE_3__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_4__ {TYPE_1__ bch; int /*<<< orphan*/  ftimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_INITIALIZED ; 
 int /*<<< orphan*/  ISDN_P_NONE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modeisar (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_isar(struct isar_hw *isar)
{
	modeisar(&isar->ch[0], ISDN_P_NONE);
	modeisar(&isar->ch[1], ISDN_P_NONE);
	del_timer(&isar->ch[0].ftimer);
	del_timer(&isar->ch[1].ftimer);
	test_and_clear_bit(FLG_INITIALIZED, &isar->ch[0].bch.Flags);
	test_and_clear_bit(FLG_INITIALIZED, &isar->ch[1].bch.Flags);
}