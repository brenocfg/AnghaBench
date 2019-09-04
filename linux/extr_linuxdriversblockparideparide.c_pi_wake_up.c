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
struct TYPE_2__ {void (* claim_cont ) () ;int claimed; int /*<<< orphan*/  parq; int /*<<< orphan*/  pardev; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  parport_claim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_spinlock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pi_wake_up(void *p)
{
	PIA *pi = (PIA *) p;
	unsigned long flags;
	void (*cont) (void) = NULL;

	spin_lock_irqsave(&pi_spinlock, flags);

	if (pi->claim_cont && !parport_claim(pi->pardev)) {
		cont = pi->claim_cont;
		pi->claim_cont = NULL;
		pi->claimed = 1;
	}

	spin_unlock_irqrestore(&pi_spinlock, flags);

	wake_up(&(pi->parq));

	if (cont)
		cont();
}