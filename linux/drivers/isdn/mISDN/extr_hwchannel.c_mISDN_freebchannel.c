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
struct bchannel {int /*<<< orphan*/  workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mISDN_clear_bchannel (struct bchannel*) ; 

void
mISDN_freebchannel(struct bchannel *ch)
{
	cancel_work_sync(&ch->workq);
	mISDN_clear_bchannel(ch);
}