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
struct wsm_scan {int num_channels; int num_ssids; int band; int type; int flags; int max_tx_rate; int num_probes; int probe_delay; TYPE_2__* ssids; TYPE_1__* ch; int /*<<< orphan*/  auto_scan_interval; } ;
struct wsm_buf {int dummy; } ;
struct cw1200_common {struct wsm_buf wsm_cmd_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ssid; int /*<<< orphan*/  length; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_chan_time; int /*<<< orphan*/  min_chan_time; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WSM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  WSM_PUT (struct wsm_buf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WSM_PUT16 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT32 (struct wsm_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSM_PUT8 (struct wsm_buf*,int) ; 
 int /*<<< orphan*/  WSM_START_SCAN_REQ_ID ; 
 int /*<<< orphan*/  wsm_cmd_lock (struct cw1200_common*) ; 
 int wsm_cmd_send (struct cw1200_common*,struct wsm_buf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_cmd_unlock (struct cw1200_common*) ; 

int wsm_scan(struct cw1200_common *priv, const struct wsm_scan *arg)
{
	int i;
	int ret;
	struct wsm_buf *buf = &priv->wsm_cmd_buf;

	if (arg->num_channels > 48)
		return -EINVAL;

	if (arg->num_ssids > 2)
		return -EINVAL;

	if (arg->band > 1)
		return -EINVAL;

	wsm_cmd_lock(priv);

	WSM_PUT8(buf, arg->band);
	WSM_PUT8(buf, arg->type);
	WSM_PUT8(buf, arg->flags);
	WSM_PUT8(buf, arg->max_tx_rate);
	WSM_PUT32(buf, arg->auto_scan_interval);
	WSM_PUT8(buf, arg->num_probes);
	WSM_PUT8(buf, arg->num_channels);
	WSM_PUT8(buf, arg->num_ssids);
	WSM_PUT8(buf, arg->probe_delay);

	for (i = 0; i < arg->num_channels; ++i) {
		WSM_PUT16(buf, arg->ch[i].number);
		WSM_PUT16(buf, 0);
		WSM_PUT32(buf, arg->ch[i].min_chan_time);
		WSM_PUT32(buf, arg->ch[i].max_chan_time);
		WSM_PUT32(buf, 0);
	}

	for (i = 0; i < arg->num_ssids; ++i) {
		WSM_PUT32(buf, arg->ssids[i].length);
		WSM_PUT(buf, &arg->ssids[i].ssid[0],
			sizeof(arg->ssids[i].ssid));
	}

	ret = wsm_cmd_send(priv, buf, NULL,
			   WSM_START_SCAN_REQ_ID, WSM_CMD_TIMEOUT);
	wsm_cmd_unlock(priv);
	return ret;

nomem:
	wsm_cmd_unlock(priv);
	return -ENOMEM;
}