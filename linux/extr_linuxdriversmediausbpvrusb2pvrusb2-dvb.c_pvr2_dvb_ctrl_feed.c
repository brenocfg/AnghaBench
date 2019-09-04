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
struct pvr2_dvb_adapter {scalar_t__ feedcount; int /*<<< orphan*/  lock; } ;
struct dvb_demux_feed {TYPE_1__* demux; } ;
struct TYPE_2__ {struct pvr2_dvb_adapter* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PVR2_TRACE_DVB_FEED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvr2_dvb_stream_end (struct pvr2_dvb_adapter*) ; 
 int pvr2_dvb_stream_start (struct pvr2_dvb_adapter*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pvr2_dvb_ctrl_feed(struct dvb_demux_feed *dvbdmxfeed, int onoff)
{
	struct pvr2_dvb_adapter *adap = dvbdmxfeed->demux->priv;
	int ret = 0;

	if (adap == NULL) return -ENODEV;

	mutex_lock(&adap->lock);
	do {
		if (onoff) {
			if (!adap->feedcount) {
				pvr2_trace(PVR2_TRACE_DVB_FEED,
					   "start feeding demux");
				ret = pvr2_dvb_stream_start(adap);
				if (ret < 0) break;
			}
			(adap->feedcount)++;
		} else if (adap->feedcount > 0) {
			(adap->feedcount)--;
			if (!adap->feedcount) {
				pvr2_trace(PVR2_TRACE_DVB_FEED,
					   "stop feeding demux");
				pvr2_dvb_stream_end(adap);
			}
		}
	} while (0);
	mutex_unlock(&adap->lock);

	return ret;
}