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
struct fb_info {struct arcfb_par* par; } ;
struct arcfb_par {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KS_CLRINT ; 
 unsigned char KS_INTACK ; 
 int /*<<< orphan*/  arcfb_waitq ; 
 unsigned char ks108_readb_ctl2 (struct arcfb_par*) ; 
 int /*<<< orphan*/  ks108_writeb_mainctl (struct arcfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t arcfb_interrupt(int vec, void *dev_instance)
{
	struct fb_info *info = dev_instance;
	unsigned char ctl2status;
	struct arcfb_par *par = info->par;

	ctl2status = ks108_readb_ctl2(par);

	if (!(ctl2status & KS_INTACK)) /* not arc generated interrupt */
		return IRQ_NONE;

	ks108_writeb_mainctl(par, KS_CLRINT);

	spin_lock(&par->lock);
        if (waitqueue_active(&arcfb_waitq)) {
                wake_up(&arcfb_waitq);
        }
	spin_unlock(&par->lock);

	return IRQ_HANDLED;
}