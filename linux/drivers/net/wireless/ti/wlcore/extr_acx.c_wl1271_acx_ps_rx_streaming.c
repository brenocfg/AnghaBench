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
typedef  int u32 ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271_acx_ps_rx_streaming {int tid; int enable; int /*<<< orphan*/  timeout; int /*<<< orphan*/  period; int /*<<< orphan*/  role_id; } ;
struct TYPE_3__ {int queues; int /*<<< orphan*/  interval; } ;
struct TYPE_4__ {TYPE_1__ rx_streaming; } ;
struct wl1271 {TYPE_2__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_PS_RX_STREAMING ; 
 int BIT (int) ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl1271_acx_ps_rx_streaming*) ; 
 struct wl1271_acx_ps_rx_streaming* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_configure (struct wl1271*,int /*<<< orphan*/ ,struct wl1271_acx_ps_rx_streaming*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

int wl1271_acx_ps_rx_streaming(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			       bool enable)
{
	struct wl1271_acx_ps_rx_streaming *rx_streaming;
	u32 conf_queues, enable_queues;
	int i, ret = 0;

	wl1271_debug(DEBUG_ACX, "acx ps rx streaming");

	rx_streaming = kzalloc(sizeof(*rx_streaming), GFP_KERNEL);
	if (!rx_streaming) {
		ret = -ENOMEM;
		goto out;
	}

	conf_queues = wl->conf.rx_streaming.queues;
	if (enable)
		enable_queues = conf_queues;
	else
		enable_queues = 0;

	for (i = 0; i < 8; i++) {
		/*
		 * Skip non-changed queues, to avoid redundant acxs.
		 * this check assumes conf.rx_streaming.queues can't
		 * be changed while rx_streaming is enabled.
		 */
		if (!(conf_queues & BIT(i)))
			continue;

		rx_streaming->role_id = wlvif->role_id;
		rx_streaming->tid = i;
		rx_streaming->enable = enable_queues & BIT(i);
		rx_streaming->period = wl->conf.rx_streaming.interval;
		rx_streaming->timeout = wl->conf.rx_streaming.interval;

		ret = wl1271_cmd_configure(wl, ACX_PS_RX_STREAMING,
					   rx_streaming,
					   sizeof(*rx_streaming));
		if (ret < 0) {
			wl1271_warning("acx ps rx streaming failed: %d", ret);
			goto out;
		}
	}
out:
	kfree(rx_streaming);
	return ret;
}