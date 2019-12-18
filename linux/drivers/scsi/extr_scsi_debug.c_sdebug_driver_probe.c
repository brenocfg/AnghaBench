#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdebug_host_info {int /*<<< orphan*/  dev; struct Scsi_Host* shost; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ this_id; scalar_t__ max_lun; scalar_t__ max_id; scalar_t__ hostdata; scalar_t__ nr_hw_queues; } ;
typedef  int /*<<< orphan*/  sdbg_host ;
struct TYPE_3__ {scalar_t__ dma_boundary; int /*<<< orphan*/  can_queue; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SCSI_W_LUN_REPORT_LUNS ; 
 int SDEBUG_OPT_ALL_INJECTING ; 
 int SDEBUG_OPT_NOISE ; 
 int SHOST_DIF_TYPE1_PROTECTION ; 
 int SHOST_DIF_TYPE2_PROTECTION ; 
 int SHOST_DIF_TYPE3_PROTECTION ; 
 int /*<<< orphan*/  SHOST_DIX_GUARD_CRC ; 
 int /*<<< orphan*/  SHOST_DIX_GUARD_IP ; 
 int SHOST_DIX_TYPE0_PROTECTION ; 
 int SHOST_DIX_TYPE1_PROTECTION ; 
 int SHOST_DIX_TYPE2_PROTECTION ; 
 int SHOST_DIX_TYPE3_PROTECTION ; 
#define  T10_PI_TYPE1_PROTECTION 130 
#define  T10_PI_TYPE2_PROTECTION 129 
#define  T10_PI_TYPE3_PROTECTION 128 
 scalar_t__ have_dif_prot ; 
 int /*<<< orphan*/  my_name ; 
 scalar_t__ nr_cpu_ids ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_host_set_guard (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_host_set_prot (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 
 int sdebug_any_injecting_opt ; 
 int /*<<< orphan*/  sdebug_clustering ; 
 int sdebug_dif ; 
 scalar_t__ sdebug_dix ; 
 TYPE_1__ sdebug_driver_template ; 
 scalar_t__ sdebug_every_nth ; 
 int sdebug_guard ; 
 int /*<<< orphan*/  sdebug_max_queue ; 
 scalar_t__ sdebug_num_tgts ; 
 int sdebug_opts ; 
 int sdebug_statistics ; 
 int sdebug_verbose ; 
 scalar_t__ submit_queues ; 
 struct sdebug_host_info* to_sdebug_host (struct device*) ; 

__attribute__((used)) static int sdebug_driver_probe(struct device *dev)
{
	int error = 0;
	struct sdebug_host_info *sdbg_host;
	struct Scsi_Host *hpnt;
	int hprot;

	sdbg_host = to_sdebug_host(dev);

	sdebug_driver_template.can_queue = sdebug_max_queue;
	if (!sdebug_clustering)
		sdebug_driver_template.dma_boundary = PAGE_SIZE - 1;

	hpnt = scsi_host_alloc(&sdebug_driver_template, sizeof(sdbg_host));
	if (NULL == hpnt) {
		pr_err("scsi_host_alloc failed\n");
		error = -ENODEV;
		return error;
	}
	if (submit_queues > nr_cpu_ids) {
		pr_warn("%s: trim submit_queues (was %d) to nr_cpu_ids=%u\n",
			my_name, submit_queues, nr_cpu_ids);
		submit_queues = nr_cpu_ids;
	}
	/* Decide whether to tell scsi subsystem that we want mq */
	/* Following should give the same answer for each host */
	hpnt->nr_hw_queues = submit_queues;

	sdbg_host->shost = hpnt;
	*((struct sdebug_host_info **)hpnt->hostdata) = sdbg_host;
	if ((hpnt->this_id >= 0) && (sdebug_num_tgts > hpnt->this_id))
		hpnt->max_id = sdebug_num_tgts + 1;
	else
		hpnt->max_id = sdebug_num_tgts;
	/* = sdebug_max_luns; */
	hpnt->max_lun = SCSI_W_LUN_REPORT_LUNS + 1;

	hprot = 0;

	switch (sdebug_dif) {

	case T10_PI_TYPE1_PROTECTION:
		hprot = SHOST_DIF_TYPE1_PROTECTION;
		if (sdebug_dix)
			hprot |= SHOST_DIX_TYPE1_PROTECTION;
		break;

	case T10_PI_TYPE2_PROTECTION:
		hprot = SHOST_DIF_TYPE2_PROTECTION;
		if (sdebug_dix)
			hprot |= SHOST_DIX_TYPE2_PROTECTION;
		break;

	case T10_PI_TYPE3_PROTECTION:
		hprot = SHOST_DIF_TYPE3_PROTECTION;
		if (sdebug_dix)
			hprot |= SHOST_DIX_TYPE3_PROTECTION;
		break;

	default:
		if (sdebug_dix)
			hprot |= SHOST_DIX_TYPE0_PROTECTION;
		break;
	}

	scsi_host_set_prot(hpnt, hprot);

	if (have_dif_prot || sdebug_dix)
		pr_info("host protection%s%s%s%s%s%s%s\n",
			(hprot & SHOST_DIF_TYPE1_PROTECTION) ? " DIF1" : "",
			(hprot & SHOST_DIF_TYPE2_PROTECTION) ? " DIF2" : "",
			(hprot & SHOST_DIF_TYPE3_PROTECTION) ? " DIF3" : "",
			(hprot & SHOST_DIX_TYPE0_PROTECTION) ? " DIX0" : "",
			(hprot & SHOST_DIX_TYPE1_PROTECTION) ? " DIX1" : "",
			(hprot & SHOST_DIX_TYPE2_PROTECTION) ? " DIX2" : "",
			(hprot & SHOST_DIX_TYPE3_PROTECTION) ? " DIX3" : "");

	if (sdebug_guard == 1)
		scsi_host_set_guard(hpnt, SHOST_DIX_GUARD_IP);
	else
		scsi_host_set_guard(hpnt, SHOST_DIX_GUARD_CRC);

	sdebug_verbose = !!(SDEBUG_OPT_NOISE & sdebug_opts);
	sdebug_any_injecting_opt = !!(SDEBUG_OPT_ALL_INJECTING & sdebug_opts);
	if (sdebug_every_nth)	/* need stats counters for every_nth */
		sdebug_statistics = true;
	error = scsi_add_host(hpnt, &sdbg_host->dev);
	if (error) {
		pr_err("scsi_add_host failed\n");
		error = -ENODEV;
		scsi_host_put(hpnt);
	} else
		scsi_scan_host(hpnt);

	return error;
}