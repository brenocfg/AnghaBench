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
struct host1x_channel {int dummy; } ;
struct host1x_cdma {int running; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDMA_EVENT_SYNC_QUEUE_EMPTY ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMACTRL ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMACTRL_DMASTOP ; 
 struct host1x_channel* cdma_to_channel (struct host1x_cdma*) ; 
 int /*<<< orphan*/  host1x_cdma_wait_locked (struct host1x_cdma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_ch_writel (struct host1x_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cdma_stop(struct host1x_cdma *cdma)
{
	struct host1x_channel *ch = cdma_to_channel(cdma);

	mutex_lock(&cdma->lock);

	if (cdma->running) {
		host1x_cdma_wait_locked(cdma, CDMA_EVENT_SYNC_QUEUE_EMPTY);
		host1x_ch_writel(ch, HOST1X_CHANNEL_DMACTRL_DMASTOP,
				 HOST1X_CHANNEL_DMACTRL);
		cdma->running = false;
	}

	mutex_unlock(&cdma->lock);
}