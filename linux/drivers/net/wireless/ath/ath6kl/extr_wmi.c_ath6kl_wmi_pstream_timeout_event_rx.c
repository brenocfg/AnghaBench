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
typedef  int /*<<< orphan*/  u8 ;
struct wmi_pstream_timeout_event {size_t traffic_class; } ;
struct wmi {int fat_pipe_exist; int /*<<< orphan*/  parent_dev; int /*<<< orphan*/  lock; scalar_t__* stream_exist_for_ac; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t WMM_NUM_AC ; 
 int /*<<< orphan*/  ath6kl_err (char*,size_t) ; 
 int /*<<< orphan*/  ath6kl_indicate_tx_activity (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath6kl_wmi_pstream_timeout_event_rx(struct wmi *wmi, u8 *datap,
					       int len)
{
	struct wmi_pstream_timeout_event *ev;

	if (len < sizeof(struct wmi_pstream_timeout_event))
		return -EINVAL;

	ev = (struct wmi_pstream_timeout_event *) datap;
	if (ev->traffic_class >= WMM_NUM_AC) {
		ath6kl_err("invalid traffic class: %d\n", ev->traffic_class);
		return -EINVAL;
	}

	/*
	 * When the pstream (fat pipe == AC) timesout, it means there were
	 * no thinStreams within this pstream & it got implicitly created
	 * due to data flow on this AC. We start the inactivity timer only
	 * for implicitly created pstream. Just reset the host state.
	 */
	spin_lock_bh(&wmi->lock);
	wmi->stream_exist_for_ac[ev->traffic_class] = 0;
	wmi->fat_pipe_exist &= ~(1 << ev->traffic_class);
	spin_unlock_bh(&wmi->lock);

	/* Indicate inactivity to driver layer for this fatpipe (pstream) */
	ath6kl_indicate_tx_activity(wmi->parent_dev, ev->traffic_class, false);

	return 0;
}