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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  spinlock; } ;
struct TYPE_3__ {scalar_t__ alive; } ;

/* Variables and functions */
 scalar_t__ init_pos ; 
 TYPE_2__ speakup_info ; 
 int /*<<< orphan*/  speakup_start_ttys () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ synth_soft ; 

__attribute__((used)) static int softsynth_close(struct inode *inode, struct file *fp)
{
	unsigned long flags;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	synth_soft.alive = 0;
	init_pos = 0;
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
	/* Make sure we let applications go before leaving */
	speakup_start_ttys();
	return 0;
}