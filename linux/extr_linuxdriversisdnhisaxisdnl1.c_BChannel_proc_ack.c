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
struct BCState {int ackcnt; int /*<<< orphan*/  st; int /*<<< orphan*/  aclock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lli_writewakeup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
BChannel_proc_ack(struct BCState *bcs)
{
	u_long	flags;
	int	ack;

	spin_lock_irqsave(&bcs->aclock, flags);
	ack = bcs->ackcnt;
	bcs->ackcnt = 0;
	spin_unlock_irqrestore(&bcs->aclock, flags);
	if (ack)
		lli_writewakeup(bcs->st, ack);
}