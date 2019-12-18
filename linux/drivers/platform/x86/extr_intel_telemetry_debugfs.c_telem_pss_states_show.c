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
typedef  int u64 ;
typedef  int u32 ;
struct telemetry_evtlog {int telem_evtlog; scalar_t__ telem_evtid; } ;
struct telemetry_debugfs_conf {scalar_t__ pss_idle_id; int pss_idle_evts; scalar_t__ pcs_idle_blkd_id; int pcs_idle_blkd_evts; scalar_t__ pcs_s0ix_blkd_id; int pcs_s0ix_blkd_evts; scalar_t__ pss_wakeup_id; int pss_wakeup_evts; scalar_t__ pss_ltr_blocking_id; int pss_ltr_evts; scalar_t__ pstates_id; TYPE_1__* pss_wakeup; TYPE_1__* pss_ltr_data; TYPE_1__* pcs_s0ix_blkd_data; TYPE_1__* pcs_idle_blkd_data; TYPE_1__* pss_idle_data; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int bit_pos; int name; } ;

/* Variables and functions */
 int TELEM_APL_MASK_PCS_STATE ; 
 int /*<<< orphan*/  TELEM_CHECK_AND_PARSE_EVTS (scalar_t__,int,int*,int,TYPE_1__*,int) ; 
 int TELEM_MASK_BIT ; 
 int TELEM_MASK_BYTE ; 
 int TELEM_MAX_OS_ALLOCATED_EVENTS ; 
 int /*<<< orphan*/  TELEM_PSS ; 
 int TELEM_PSS_IDLE_BLOCKED_EVTS ; 
 int TELEM_PSS_IDLE_EVTS ; 
 int TELEM_PSS_LTR_BLOCKING_EVTS ; 
 int TELEM_PSS_S0IX_BLOCKED_EVTS ; 
 int TELEM_PSS_S0IX_WAKEUP_EVTS ; 
 struct telemetry_debugfs_conf* debugfs_conf ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int telemetry_get_evtname (int /*<<< orphan*/ ,char const**,int) ; 
 int telemetry_read_eventlog (int /*<<< orphan*/ ,struct telemetry_evtlog*,int) ; 

__attribute__((used)) static int telem_pss_states_show(struct seq_file *s, void *unused)
{
	struct telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	struct telemetry_debugfs_conf *conf = debugfs_conf;
	const char *name[TELEM_MAX_OS_ALLOCATED_EVENTS];
	u32 pcs_idle_blkd[TELEM_PSS_IDLE_BLOCKED_EVTS],
	    pcs_s0ix_blkd[TELEM_PSS_S0IX_BLOCKED_EVTS],
	    pss_s0ix_wakeup[TELEM_PSS_S0IX_WAKEUP_EVTS],
	    pss_ltr_blkd[TELEM_PSS_LTR_BLOCKING_EVTS],
	    pss_idle[TELEM_PSS_IDLE_EVTS];
	int index, idx, ret, err = 0;
	u64 pstates = 0;

	ret = telemetry_read_eventlog(TELEM_PSS, evtlog,
				      TELEM_MAX_OS_ALLOCATED_EVENTS);
	if (ret < 0)
		return ret;

	err = telemetry_get_evtname(TELEM_PSS, name,
				    TELEM_MAX_OS_ALLOCATED_EVENTS);
	if (err < 0)
		return err;

	seq_puts(s, "\n----------------------------------------------------\n");
	seq_puts(s, "\tPSS TELEM EVENTLOG (Residency = field/19.2 us\n");
	seq_puts(s, "----------------------------------------------------\n");
	for (index = 0; index < ret; index++) {
		seq_printf(s, "%-32s %llu\n",
			   name[index], evtlog[index].telem_evtlog);

		/* Fetch PSS IDLE State */
		if (evtlog[index].telem_evtid == conf->pss_idle_id) {
			pss_idle[conf->pss_idle_evts - 1] =
			(evtlog[index].telem_evtlog >>
			conf->pss_idle_data[conf->pss_idle_evts - 1].bit_pos) &
			TELEM_APL_MASK_PCS_STATE;
		}

		TELEM_CHECK_AND_PARSE_EVTS(conf->pss_idle_id,
					   conf->pss_idle_evts - 1,
					   pss_idle, evtlog[index].telem_evtlog,
					   conf->pss_idle_data, TELEM_MASK_BIT);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pcs_idle_blkd_id,
					   conf->pcs_idle_blkd_evts,
					   pcs_idle_blkd,
					   evtlog[index].telem_evtlog,
					   conf->pcs_idle_blkd_data,
					   TELEM_MASK_BYTE);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pcs_s0ix_blkd_id,
					   conf->pcs_s0ix_blkd_evts,
					   pcs_s0ix_blkd,
					   evtlog[index].telem_evtlog,
					   conf->pcs_s0ix_blkd_data,
					   TELEM_MASK_BYTE);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pss_wakeup_id,
					   conf->pss_wakeup_evts,
					   pss_s0ix_wakeup,
					   evtlog[index].telem_evtlog,
					   conf->pss_wakeup, TELEM_MASK_BYTE);

		TELEM_CHECK_AND_PARSE_EVTS(conf->pss_ltr_blocking_id,
					   conf->pss_ltr_evts, pss_ltr_blkd,
					   evtlog[index].telem_evtlog,
					   conf->pss_ltr_data, TELEM_MASK_BYTE);

		if (evtlog[index].telem_evtid == debugfs_conf->pstates_id)
			pstates = evtlog[index].telem_evtlog;
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PStates\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Domain\t\t\t\tFreq(Mhz)\n");
	seq_printf(s, " IA\t\t\t\t %llu\n GT\t\t\t\t %llu\n",
		   (pstates & TELEM_MASK_BYTE)*100,
		   ((pstates >> 8) & TELEM_MASK_BYTE)*50/3);

	seq_printf(s, " IUNIT\t\t\t\t %llu\n SA\t\t\t\t %llu\n",
		   ((pstates >> 16) & TELEM_MASK_BYTE)*25,
		   ((pstates >> 24) & TELEM_MASK_BYTE)*50/3);

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PSS IDLE Status\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Device\t\t\t\t\tIDLE\n");
	for (index = 0; index < debugfs_conf->pss_idle_evts; index++) {
		seq_printf(s, "%-32s\t%u\n",
			   debugfs_conf->pss_idle_data[index].name,
			   pss_idle[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PSS Idle blkd Status (~1ms saturating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Blocker\t\t\t\t\tCount\n");
	for (index = 0; index < debugfs_conf->pcs_idle_blkd_evts; index++) {
		seq_printf(s, "%-32s\t%u\n",
			   debugfs_conf->pcs_idle_blkd_data[index].name,
			   pcs_idle_blkd[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PSS S0ix blkd Status (~1ms saturating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Blocker\t\t\t\t\tCount\n");
	for (index = 0; index < debugfs_conf->pcs_s0ix_blkd_evts; index++) {
		seq_printf(s, "%-32s\t%u\n",
			   debugfs_conf->pcs_s0ix_blkd_data[index].name,
			   pcs_s0ix_blkd[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "LTR Blocking Status (~1ms saturating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Blocker\t\t\t\t\tCount\n");
	for (index = 0; index < debugfs_conf->pss_ltr_evts; index++) {
		seq_printf(s, "%-32s\t%u\n",
			   debugfs_conf->pss_ltr_data[index].name,
			   pss_s0ix_wakeup[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "Wakes Status (~1ms saturating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Wakes\t\t\t\t\tCount\n");
	for (index = 0; index < debugfs_conf->pss_wakeup_evts; index++) {
		seq_printf(s, "%-32s\t%u\n",
			   debugfs_conf->pss_wakeup[index].name,
			   pss_ltr_blkd[index]);
	}

	return 0;
}