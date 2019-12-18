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
struct dvb_demux {int* pids; struct av7110* priv; } ;
struct av7110 {int /*<<< orphan*/  full_ts; scalar_t__ fe_synced; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMTYPE_PIDFILTER ; 
 int ChangePIDs (struct av7110*,int,int,int,int,int) ; 
 int /*<<< orphan*/  RP_AUDIO ; 
 int /*<<< orphan*/  RP_VIDEO ; 
 int /*<<< orphan*/  Scan ; 
 int StartHWFilter (int /*<<< orphan*/ ) ; 
 int TS_PACKET ; 
 int av7110_av_start_record (struct av7110*,int /*<<< orphan*/ ,struct dvb_demux_feed*) ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 

__attribute__((used)) static int dvb_feed_start_pid(struct dvb_demux_feed *dvbdmxfeed)
{
	struct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	struct av7110 *av7110 = dvbdmx->priv;
	u16 *pid = dvbdmx->pids, npids[5];
	int i;
	int ret = 0;

	dprintk(4, "%p\n", av7110);

	npids[0] = npids[1] = npids[2] = npids[3] = npids[4] = 0xffff;
	i = dvbdmxfeed->pes_type;
	npids[i] = (pid[i]&0x8000) ? 0 : pid[i];
	if ((i == 2) && npids[i] && (dvbdmxfeed->ts_type & TS_PACKET)) {
		npids[i] = 0;
		ret = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
		if (!ret)
			ret = StartHWFilter(dvbdmxfeed->filter);
		return ret;
	}
	if (dvbdmxfeed->pes_type <= 2 || dvbdmxfeed->pes_type == 4) {
		ret = ChangePIDs(av7110, npids[1], npids[0], npids[2], npids[3], npids[4]);
		if (ret)
			return ret;
	}

	if (dvbdmxfeed->pes_type < 2 && npids[0])
		if (av7110->fe_synced)
		{
			ret = av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, Scan, 0);
			if (ret)
				return ret;
		}

	if ((dvbdmxfeed->ts_type & TS_PACKET) && !av7110->full_ts) {
		if (dvbdmxfeed->pes_type == 0 && !(dvbdmx->pids[0] & 0x8000))
			ret = av7110_av_start_record(av7110, RP_AUDIO, dvbdmxfeed);
		if (dvbdmxfeed->pes_type == 1 && !(dvbdmx->pids[1] & 0x8000))
			ret = av7110_av_start_record(av7110, RP_VIDEO, dvbdmxfeed);
	}
	return ret;
}