#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  r; } ;
struct TYPE_6__ {int /*<<< orphan*/  r; } ;
struct TYPE_5__ {int /*<<< orphan*/  r; } ;
struct TYPE_8__ {TYPE_3__ autopoll; TYPE_2__ active_lo; TYPE_1__ active_hi; } ;

/* Variables and functions */
 int APE ; 
 TYPE_4__* adb ; 
 int /*<<< orphan*/  macio_lock ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int macio_adb_autopoll(int devs)
{
	unsigned long flags;
	
	spin_lock_irqsave(&macio_lock, flags);
	out_8(&adb->active_hi.r, devs >> 8);
	out_8(&adb->active_lo.r, devs);
	out_8(&adb->autopoll.r, devs? APE: 0);
	spin_unlock_irqrestore(&macio_lock, flags);
	return 0;
}