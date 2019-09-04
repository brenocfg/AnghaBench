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
struct pblk {int /*<<< orphan*/  wtimer; int /*<<< orphan*/  writer_ts; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void pblk_write_kick(struct pblk *pblk)
{
	wake_up_process(pblk->writer_ts);
	mod_timer(&pblk->wtimer, jiffies + msecs_to_jiffies(1000));
}