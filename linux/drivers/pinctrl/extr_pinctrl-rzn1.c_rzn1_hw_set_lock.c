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
typedef  int u8 ;
typedef  int u32 ;
struct rzn1_pinctrl {int lev1_protect_phys; int lev2_protect_phys; TYPE_1__* lev2; TYPE_2__* lev1; } ;
struct TYPE_4__ {int /*<<< orphan*/  status_protect; } ;
struct TYPE_3__ {int /*<<< orphan*/  status_protect; } ;

/* Variables and functions */
 int LOCK_LEVEL1 ; 
 int LOCK_LEVEL2 ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rzn1_hw_set_lock(struct rzn1_pinctrl *ipctl, u8 lock, u8 value)
{
	/*
	 * The pinmux configuration is locked by writing the physical address of
	 * the status_protect register to itself. It is unlocked by writing the
	 * address | 1.
	 */
	if (lock & LOCK_LEVEL1) {
		u32 val = ipctl->lev1_protect_phys | !(value & LOCK_LEVEL1);

		writel(val, &ipctl->lev1->status_protect);
	}

	if (lock & LOCK_LEVEL2) {
		u32 val = ipctl->lev2_protect_phys | !(value & LOCK_LEVEL2);

		writel(val, &ipctl->lev2->status_protect);
	}
}