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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_AVAIL_TIME_OUT ; 
 scalar_t__ RCV_BTH_QP ; 
 scalar_t__ RCV_BYPASS ; 
 scalar_t__ RCV_COUNTER_ARRAY32 ; 
 scalar_t__ RCV_COUNTER_ARRAY64 ; 
 scalar_t__ RCV_CTRL ; 
 int /*<<< orphan*/  RCV_CTXT_CTRL ; 
 int /*<<< orphan*/  RCV_EGR_CTRL ; 
 scalar_t__ RCV_EGR_INDEX_HEAD ; 
 scalar_t__ RCV_ERR_CLEAR ; 
 scalar_t__ RCV_ERR_INFO ; 
 unsigned long long RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK ; 
 scalar_t__ RCV_ERR_MASK ; 
 int /*<<< orphan*/  RCV_HDR_ADDR ; 
 int /*<<< orphan*/  RCV_HDR_CNT ; 
 int /*<<< orphan*/  RCV_HDR_ENT_SIZE ; 
 scalar_t__ RCV_HDR_HEAD ; 
 int /*<<< orphan*/  RCV_HDR_OVFL_CNT ; 
 int /*<<< orphan*/  RCV_HDR_SIZE ; 
 int /*<<< orphan*/  RCV_HDR_TAIL_ADDR ; 
 int /*<<< orphan*/  RCV_KEY_CTRL ; 
 scalar_t__ RCV_MULTICAST ; 
 scalar_t__ RCV_PARTITION_KEY ; 
 scalar_t__ RCV_QP_MAP_TABLE ; 
 scalar_t__ RCV_RSM_MAP_TABLE ; 
 int /*<<< orphan*/  RCV_TID_CTRL ; 
 scalar_t__ RCV_TID_FLOW_TABLE ; 
 scalar_t__ RCV_VL15 ; 
 int RXE_NUM_32_BIT_COUNTERS ; 
 int RXE_NUM_64_BIT_COUNTERS ; 
 int RXE_NUM_RSM_INSTANCES ; 
 int RXE_NUM_TID_FLOWS ; 
 int chip_rcv_contexts (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  clear_rsm_rule (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  init_rbufs (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uctxt_csr (struct hfi1_devdata*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_rxe_csrs(struct hfi1_devdata *dd)
{
	int i, j;

	/*
	 * RXE Kernel CSRs
	 */
	write_csr(dd, RCV_CTRL, 0);
	init_rbufs(dd);
	/* RCV_STATUS read-only */
	/* RCV_CONTEXTS read-only */
	/* RCV_ARRAY_CNT read-only */
	/* RCV_BUF_SIZE read-only */
	write_csr(dd, RCV_BTH_QP, 0);
	write_csr(dd, RCV_MULTICAST, 0);
	write_csr(dd, RCV_BYPASS, 0);
	write_csr(dd, RCV_VL15, 0);
	/* this is a clear-down */
	write_csr(dd, RCV_ERR_INFO,
		  RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK);
	/* RCV_ERR_STATUS read-only */
	write_csr(dd, RCV_ERR_MASK, 0);
	write_csr(dd, RCV_ERR_CLEAR, ~0ull);
	/* RCV_ERR_FORCE leave alone */
	for (i = 0; i < 32; i++)
		write_csr(dd, RCV_QP_MAP_TABLE + (8 * i), 0);
	for (i = 0; i < 4; i++)
		write_csr(dd, RCV_PARTITION_KEY + (8 * i), 0);
	for (i = 0; i < RXE_NUM_32_BIT_COUNTERS; i++)
		write_csr(dd, RCV_COUNTER_ARRAY32 + (8 * i), 0);
	for (i = 0; i < RXE_NUM_64_BIT_COUNTERS; i++)
		write_csr(dd, RCV_COUNTER_ARRAY64 + (8 * i), 0);
	for (i = 0; i < RXE_NUM_RSM_INSTANCES; i++)
		clear_rsm_rule(dd, i);
	for (i = 0; i < 32; i++)
		write_csr(dd, RCV_RSM_MAP_TABLE + (8 * i), 0);

	/*
	 * RXE Kernel and User Per-Context CSRs
	 */
	for (i = 0; i < chip_rcv_contexts(dd); i++) {
		/* kernel */
		write_kctxt_csr(dd, i, RCV_CTXT_CTRL, 0);
		/* RCV_CTXT_STATUS read-only */
		write_kctxt_csr(dd, i, RCV_EGR_CTRL, 0);
		write_kctxt_csr(dd, i, RCV_TID_CTRL, 0);
		write_kctxt_csr(dd, i, RCV_KEY_CTRL, 0);
		write_kctxt_csr(dd, i, RCV_HDR_ADDR, 0);
		write_kctxt_csr(dd, i, RCV_HDR_CNT, 0);
		write_kctxt_csr(dd, i, RCV_HDR_ENT_SIZE, 0);
		write_kctxt_csr(dd, i, RCV_HDR_SIZE, 0);
		write_kctxt_csr(dd, i, RCV_HDR_TAIL_ADDR, 0);
		write_kctxt_csr(dd, i, RCV_AVAIL_TIME_OUT, 0);
		write_kctxt_csr(dd, i, RCV_HDR_OVFL_CNT, 0);

		/* user */
		/* RCV_HDR_TAIL read-only */
		write_uctxt_csr(dd, i, RCV_HDR_HEAD, 0);
		/* RCV_EGR_INDEX_TAIL read-only */
		write_uctxt_csr(dd, i, RCV_EGR_INDEX_HEAD, 0);
		/* RCV_EGR_OFFSET_TAIL read-only */
		for (j = 0; j < RXE_NUM_TID_FLOWS; j++) {
			write_uctxt_csr(dd, i,
					RCV_TID_FLOW_TABLE + (8 * j), 0);
		}
	}
}