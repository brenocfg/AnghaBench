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
typedef  int /*<<< orphan*/  u_long ;
struct ahc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int ahc_intr (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*,int /*<<< orphan*/ *) ; 

irqreturn_t
ahc_linux_isr(int irq, void *dev_id)
{
	struct	ahc_softc *ahc;
	u_long	flags;
	int	ours;

	ahc = (struct ahc_softc *) dev_id;
	ahc_lock(ahc, &flags); 
	ours = ahc_intr(ahc);
	ahc_unlock(ahc, &flags);
	return IRQ_RETVAL(ours);
}