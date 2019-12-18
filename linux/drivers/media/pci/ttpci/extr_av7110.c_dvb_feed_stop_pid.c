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
typedef  int u16 ;
struct dvb_demux_feed {int pes_type; int ts_type; int /*<<< orphan*/  filter; struct dvb_demux* demux; } ;
struct dvb_demux {int* pids; scalar_t__ playing; scalar_t__ recording; struct av7110* priv; } ;
struct av7110 {int /*<<< orphan*/  playing; int /*<<< orphan*/  rec_mode; } ;

/* Variables and functions */
 int ChangePIDs (struct av7110*,int,int,int,int,int) ; 
 int /*<<< orphan*/  RP_AUDIO ; 
 int /*<<< orphan*/  RP_VIDEO ; 
 int StopHWFilter (int /*<<< orphan*/ ) ; 
 int TS_PACKET ; 
 int av7110_av_stop (struct av7110*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int /*<<< orphan*/  pids_off ; 

__attribute__((used)) static int dvb_feed_stop_pid(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct av7110 *av7110 = dvbdmx->priv;
	u16 *pid = dvbdmx->pids, npids[5];
	int i;

	int ret = 0;

	dprintk(4, "%p\n", av7110);

	if (dvbdmxfeed->pes_type <= 1) {
		ret = av7110_av_stop(av7110, dvbdmxfeed->pes_type ?  RP_VIDEO : RP_AUDIO);
		if (ret)
			return ret;
		if (!av7110->rec_mode)
			dvbdmx->recording = 0;
		if (!av7110->playing)
			dvbdmx->playing = 0;
	}
	npids[0] = npids[1] = npids[2] = npids[3] = npids[4] = 0xffff;
	i = dvbdmxfeed->pes_type;
	switch (i) {
	case 2: //teletext
		if (dvbdmxfeed->ts_type & TS_PACKET)
			ret = StopHWFilter(dvbdmxfeed->filter);
		npids[2] = 0;
		break;
	case 0:
	case 1:
	case 4:
		if (!pids_off)
			return 0;
		npids[i] = (pid[i]&0x8000) ? 0 : pid[i];
		break;
	}
	if (!ret)
		ret = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
	return ret;
}