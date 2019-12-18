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
struct tty_struct {int dummy; } ;
struct asyncppp {int /*<<< orphan*/  tsk; int /*<<< orphan*/  rqueue; int /*<<< orphan*/  recv_lock; } ;

/* Variables and functions */
 struct asyncppp* ap_get (struct tty_struct*) ; 
 int /*<<< orphan*/  ap_put (struct asyncppp*) ; 
 int /*<<< orphan*/  ppp_async_input (struct asyncppp*,unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unthrottle (struct tty_struct*) ; 

__attribute__((used)) static void
ppp_asynctty_receive(struct tty_struct *tty, const unsigned char *buf,
		  char *cflags, int count)
{
	struct asyncppp *ap = ap_get(tty);
	unsigned long flags;

	if (!ap)
		return;
	spin_lock_irqsave(&ap->recv_lock, flags);
	ppp_async_input(ap, buf, cflags, count);
	spin_unlock_irqrestore(&ap->recv_lock, flags);
	if (!skb_queue_empty(&ap->rqueue))
		tasklet_schedule(&ap->tsk);
	ap_put(ap);
	tty_unthrottle(tty);
}