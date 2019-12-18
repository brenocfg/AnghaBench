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
struct host1x {int /*<<< orphan*/ * debug_op; int /*<<< orphan*/ * intr_op; int /*<<< orphan*/ * syncpt_op; int /*<<< orphan*/ * cdma_pb_op; int /*<<< orphan*/ * cdma_op; int /*<<< orphan*/ * channel_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_cdma_ops ; 
 int /*<<< orphan*/  host1x_channel_ops ; 
 int /*<<< orphan*/  host1x_debug_ops ; 
 int /*<<< orphan*/  host1x_intr_ops ; 
 int /*<<< orphan*/  host1x_pushbuffer_ops ; 
 int /*<<< orphan*/  host1x_syncpt_ops ; 

int host1x05_init(struct host1x *host)
{
	host->channel_op = &host1x_channel_ops;
	host->cdma_op = &host1x_cdma_ops;
	host->cdma_pb_op = &host1x_pushbuffer_ops;
	host->syncpt_op = &host1x_syncpt_ops;
	host->intr_op = &host1x_intr_ops;
	host->debug_op = &host1x_debug_ops;

	return 0;
}