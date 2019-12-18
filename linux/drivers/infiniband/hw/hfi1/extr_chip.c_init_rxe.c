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
typedef  unsigned long long u64 ;
struct rsm_map_table {int /*<<< orphan*/  used; } ;
struct TYPE_2__ {int /*<<< orphan*/  rmt_start; } ;
struct hfi1_devdata {TYPE_1__ vnic; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RCV_BYPASS ; 
 unsigned long long RCV_BYPASS_HDR_SIZE_MASK ; 
 unsigned long long RCV_BYPASS_HDR_SIZE_SHIFT ; 
 unsigned long long RCV_BYPASS_HDR_SIZE_SMASK ; 
 int /*<<< orphan*/  RCV_ERR_MASK ; 
 struct rsm_map_table* alloc_rsm_map_table (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  complete_rsm_map_table (struct hfi1_devdata*,struct rsm_map_table*) ; 
 int /*<<< orphan*/  init_fecn_handling (struct hfi1_devdata*,struct rsm_map_table*) ; 
 int /*<<< orphan*/  init_qos (struct hfi1_devdata*,struct rsm_map_table*) ; 
 int /*<<< orphan*/  kfree (struct rsm_map_table*) ; 
 unsigned long long read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int init_rxe(struct hfi1_devdata *dd)
{
	struct rsm_map_table *rmt;
	u64 val;

	/* enable all receive errors */
	write_csr(dd, RCV_ERR_MASK, ~0ull);

	rmt = alloc_rsm_map_table(dd);
	if (!rmt)
		return -ENOMEM;

	/* set up QOS, including the QPN map table */
	init_qos(dd, rmt);
	init_fecn_handling(dd, rmt);
	complete_rsm_map_table(dd, rmt);
	/* record number of used rsm map entries for vnic */
	dd->vnic.rmt_start = rmt->used;
	kfree(rmt);

	/*
	 * make sure RcvCtrl.RcvWcb <= PCIe Device Control
	 * Register Max_Payload_Size (PCI_EXP_DEVCTL in Linux PCIe config
	 * space, PciCfgCap2.MaxPayloadSize in HFI).  There is only one
	 * invalid configuration: RcvCtrl.RcvWcb set to its max of 256 and
	 * Max_PayLoad_Size set to its minimum of 128.
	 *
	 * Presently, RcvCtrl.RcvWcb is not modified from its default of 0
	 * (64 bytes).  Max_Payload_Size is possibly modified upward in
	 * tune_pcie_caps() which is called after this routine.
	 */

	/* Have 16 bytes (4DW) of bypass header available in header queue */
	val = read_csr(dd, RCV_BYPASS);
	val &= ~RCV_BYPASS_HDR_SIZE_SMASK;
	val |= ((4ull & RCV_BYPASS_HDR_SIZE_MASK) <<
		RCV_BYPASS_HDR_SIZE_SHIFT);
	write_csr(dd, RCV_BYPASS, val);
	return 0;
}