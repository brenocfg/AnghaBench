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
typedef  int /*<<< orphan*/  u32 ;
struct etmv4_drvdata {int instrp0; int trcbb; int trccond; int trccci; int retstack; int trc_error; int syncpr; int stallctl; int sysstall; int nooverflow; int atbtrig; int lpoverride; scalar_t__ base; void* nr_cntr; void* nrseqstate; void* trcid_size; void* nr_ext_inp; void* numvmidc; void* numcidc; void* nr_ss_cmp; void* nr_resource; void* nr_pe_cmp; void* nr_addr_cmp; void* nr_pe; void* ns_ex_level; void* s_ex_level; void* ccitmin; void* ccsize; void* vmid_size; void* ctxid_size; void* arch; void* ts_size; void* q_support; void* nr_event; } ;

/* Variables and functions */
 void* BMVAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CS_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CS_UNLOCK (scalar_t__) ; 
 scalar_t__ TRCIDR0 ; 
 scalar_t__ TRCIDR1 ; 
 scalar_t__ TRCIDR2 ; 
 scalar_t__ TRCIDR3 ; 
 scalar_t__ TRCIDR4 ; 
 scalar_t__ TRCIDR5 ; 
 int /*<<< orphan*/  etm4_os_unlock (struct etmv4_drvdata*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void etm4_init_arch_data(void *info)
{
	u32 etmidr0;
	u32 etmidr1;
	u32 etmidr2;
	u32 etmidr3;
	u32 etmidr4;
	u32 etmidr5;
	struct etmv4_drvdata *drvdata = info;

	/* Make sure all registers are accessible */
	etm4_os_unlock(drvdata);

	CS_UNLOCK(drvdata->base);

	/* find all capabilities of the tracing unit */
	etmidr0 = readl_relaxed(drvdata->base + TRCIDR0);

	/* INSTP0, bits[2:1] P0 tracing support field */
	if (BMVAL(etmidr0, 1, 1) && BMVAL(etmidr0, 2, 2))
		drvdata->instrp0 = true;
	else
		drvdata->instrp0 = false;

	/* TRCBB, bit[5] Branch broadcast tracing support bit */
	if (BMVAL(etmidr0, 5, 5))
		drvdata->trcbb = true;
	else
		drvdata->trcbb = false;

	/* TRCCOND, bit[6] Conditional instruction tracing support bit */
	if (BMVAL(etmidr0, 6, 6))
		drvdata->trccond = true;
	else
		drvdata->trccond = false;

	/* TRCCCI, bit[7] Cycle counting instruction bit */
	if (BMVAL(etmidr0, 7, 7))
		drvdata->trccci = true;
	else
		drvdata->trccci = false;

	/* RETSTACK, bit[9] Return stack bit */
	if (BMVAL(etmidr0, 9, 9))
		drvdata->retstack = true;
	else
		drvdata->retstack = false;

	/* NUMEVENT, bits[11:10] Number of events field */
	drvdata->nr_event = BMVAL(etmidr0, 10, 11);
	/* QSUPP, bits[16:15] Q element support field */
	drvdata->q_support = BMVAL(etmidr0, 15, 16);
	/* TSSIZE, bits[28:24] Global timestamp size field */
	drvdata->ts_size = BMVAL(etmidr0, 24, 28);

	/* base architecture of trace unit */
	etmidr1 = readl_relaxed(drvdata->base + TRCIDR1);
	/*
	 * TRCARCHMIN, bits[7:4] architecture the minor version number
	 * TRCARCHMAJ, bits[11:8] architecture major versin number
	 */
	drvdata->arch = BMVAL(etmidr1, 4, 11);

	/* maximum size of resources */
	etmidr2 = readl_relaxed(drvdata->base + TRCIDR2);
	/* CIDSIZE, bits[9:5] Indicates the Context ID size */
	drvdata->ctxid_size = BMVAL(etmidr2, 5, 9);
	/* VMIDSIZE, bits[14:10] Indicates the VMID size */
	drvdata->vmid_size = BMVAL(etmidr2, 10, 14);
	/* CCSIZE, bits[28:25] size of the cycle counter in bits minus 12 */
	drvdata->ccsize = BMVAL(etmidr2, 25, 28);

	etmidr3 = readl_relaxed(drvdata->base + TRCIDR3);
	/* CCITMIN, bits[11:0] minimum threshold value that can be programmed */
	drvdata->ccitmin = BMVAL(etmidr3, 0, 11);
	/* EXLEVEL_S, bits[19:16] Secure state instruction tracing */
	drvdata->s_ex_level = BMVAL(etmidr3, 16, 19);
	/* EXLEVEL_NS, bits[23:20] Non-secure state instruction tracing */
	drvdata->ns_ex_level = BMVAL(etmidr3, 20, 23);

	/*
	 * TRCERR, bit[24] whether a trace unit can trace a
	 * system error exception.
	 */
	if (BMVAL(etmidr3, 24, 24))
		drvdata->trc_error = true;
	else
		drvdata->trc_error = false;

	/* SYNCPR, bit[25] implementation has a fixed synchronization period? */
	if (BMVAL(etmidr3, 25, 25))
		drvdata->syncpr = true;
	else
		drvdata->syncpr = false;

	/* STALLCTL, bit[26] is stall control implemented? */
	if (BMVAL(etmidr3, 26, 26))
		drvdata->stallctl = true;
	else
		drvdata->stallctl = false;

	/* SYSSTALL, bit[27] implementation can support stall control? */
	if (BMVAL(etmidr3, 27, 27))
		drvdata->sysstall = true;
	else
		drvdata->sysstall = false;

	/* NUMPROC, bits[30:28] the number of PEs available for tracing */
	drvdata->nr_pe = BMVAL(etmidr3, 28, 30);

	/* NOOVERFLOW, bit[31] is trace overflow prevention supported */
	if (BMVAL(etmidr3, 31, 31))
		drvdata->nooverflow = true;
	else
		drvdata->nooverflow = false;

	/* number of resources trace unit supports */
	etmidr4 = readl_relaxed(drvdata->base + TRCIDR4);
	/* NUMACPAIRS, bits[0:3] number of addr comparator pairs for tracing */
	drvdata->nr_addr_cmp = BMVAL(etmidr4, 0, 3);
	/* NUMPC, bits[15:12] number of PE comparator inputs for tracing */
	drvdata->nr_pe_cmp = BMVAL(etmidr4, 12, 15);
	/*
	 * NUMRSPAIR, bits[19:16]
	 * The number of resource pairs conveyed by the HW starts at 0, i.e a
	 * value of 0x0 indicate 1 resource pair, 0x1 indicate two and so on.
	 * As such add 1 to the value of NUMRSPAIR for a better representation.
	 */
	drvdata->nr_resource = BMVAL(etmidr4, 16, 19) + 1;
	/*
	 * NUMSSCC, bits[23:20] the number of single-shot
	 * comparator control for tracing
	 */
	drvdata->nr_ss_cmp = BMVAL(etmidr4, 20, 23);
	/* NUMCIDC, bits[27:24] number of Context ID comparators for tracing */
	drvdata->numcidc = BMVAL(etmidr4, 24, 27);
	/* NUMVMIDC, bits[31:28] number of VMID comparators for tracing */
	drvdata->numvmidc = BMVAL(etmidr4, 28, 31);

	etmidr5 = readl_relaxed(drvdata->base + TRCIDR5);
	/* NUMEXTIN, bits[8:0] number of external inputs implemented */
	drvdata->nr_ext_inp = BMVAL(etmidr5, 0, 8);
	/* TRACEIDSIZE, bits[21:16] indicates the trace ID width */
	drvdata->trcid_size = BMVAL(etmidr5, 16, 21);
	/* ATBTRIG, bit[22] implementation can support ATB triggers? */
	if (BMVAL(etmidr5, 22, 22))
		drvdata->atbtrig = true;
	else
		drvdata->atbtrig = false;
	/*
	 * LPOVERRIDE, bit[23] implementation supports
	 * low-power state override
	 */
	if (BMVAL(etmidr5, 23, 23))
		drvdata->lpoverride = true;
	else
		drvdata->lpoverride = false;
	/* NUMSEQSTATE, bits[27:25] number of sequencer states implemented */
	drvdata->nrseqstate = BMVAL(etmidr5, 25, 27);
	/* NUMCNTR, bits[30:28] number of counters available for tracing */
	drvdata->nr_cntr = BMVAL(etmidr5, 28, 30);
	CS_LOCK(drvdata->base);
}