#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct telemetry_evtmap {scalar_t__ evt_id; } ;
struct telemetry_evtlog {scalar_t__ telem_evtid; int /*<<< orphan*/  telem_evtlog; } ;
struct telem_ssram_region {int /*<<< orphan*/ * events; } ;
typedef  enum telemetry_unit { ____Placeholder_telemetry_unit } telemetry_unit ;
struct TYPE_5__ {struct telemetry_evtmap* telem_evts; } ;
struct TYPE_4__ {struct telemetry_evtmap* telem_evts; } ;
struct TYPE_6__ {TYPE_2__ ioss_config; TYPE_1__ pss_config; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TELEM_IOSS 129 
 int TELEM_MAX_EVENTS_SRAM ; 
#define  TELEM_PSS 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int telem_evtlog_read (int,struct telem_ssram_region*,int) ; 
 TYPE_3__* telm_conf ; 

__attribute__((used)) static int telemetry_plt_raw_read_eventlog(enum telemetry_unit telem_unit,
					   struct telemetry_evtlog *evtlog,
					   int len, int log_all_evts)
{
	int index, idx1, ret, readlen = len;
	struct telem_ssram_region ssram_region;
	struct telemetry_evtmap *evtmap;

	switch (telem_unit)	{
	case TELEM_PSS:
		evtmap = telm_conf->pss_config.telem_evts;
		break;

	case TELEM_IOSS:
		evtmap = telm_conf->ioss_config.telem_evts;
		break;

	default:
		pr_err("Unknown Telemetry Unit Specified %d\n", telem_unit);
		return -EINVAL;
	}

	if (!log_all_evts)
		readlen = TELEM_MAX_EVENTS_SRAM;

	ret = telem_evtlog_read(telem_unit, &ssram_region, readlen);
	if (ret < 0)
		return ret;

	/* Invalid evt-id array specified via length mismatch */
	if ((!log_all_evts) && (len > ret))
		return -EINVAL;

	if (log_all_evts)
		for (index = 0; index < ret; index++) {
			evtlog[index].telem_evtlog = ssram_region.events[index];
			evtlog[index].telem_evtid = evtmap[index].evt_id;
		}
	else
		for (index = 0, readlen = 0; (index < ret) && (readlen < len);
		     index++) {
			for (idx1 = 0; idx1 < len; idx1++) {
				/* Elements matched */
				if (evtmap[index].evt_id ==
				    evtlog[idx1].telem_evtid) {
					evtlog[idx1].telem_evtlog =
					ssram_region.events[index];
					readlen++;

					break;
				}
			}
		}

	return readlen;
}