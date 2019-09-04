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
struct TYPE_3__ {int /*<<< orphan*/  (* v2_eval ) (char*) ;int /*<<< orphan*/  (* v0_eval ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_4__ {TYPE_1__ pv_fortheval; } ;

/* Variables and functions */
 scalar_t__ PROM_V0 ; 
 int /*<<< orphan*/  prom_lock ; 
 scalar_t__ prom_vers ; 
 int /*<<< orphan*/  restore_current () ; 
 TYPE_2__* romvec ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 

void
prom_feval(char *fstring)
{
	unsigned long flags;
	if(!fstring || fstring[0] == 0)
		return;
	spin_lock_irqsave(&prom_lock, flags);
	if(prom_vers == PROM_V0)
		(*(romvec->pv_fortheval.v0_eval))(strlen(fstring), fstring);
	else
		(*(romvec->pv_fortheval.v2_eval))(fstring);
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);
}