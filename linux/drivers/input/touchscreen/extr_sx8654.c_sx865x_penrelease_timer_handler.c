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
struct timer_list {int dummy; } ;
struct sx8654 {TYPE_1__* client; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct sx8654* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sx865x_penrelease (struct sx8654*) ; 
 int /*<<< orphan*/  timer ; 
 struct sx8654* ts ; 

__attribute__((used)) static void sx865x_penrelease_timer_handler(struct timer_list *t)
{
	struct sx8654 *ts = from_timer(ts, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&ts->lock, flags);
	sx865x_penrelease(ts);
	spin_unlock_irqrestore(&ts->lock, flags);
	dev_dbg(&ts->client->dev, "penrelease by timer\n");
}