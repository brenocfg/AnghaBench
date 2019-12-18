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
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_pportdata {TYPE_1__* dd; int /*<<< orphan*/ * scntrs; } ;
struct cntr_entry {int offset; } ;
struct TYPE_2__ {int num_rcv_contexts; } ;

/* Variables and functions */
 int CNTR_INVALID_VL ; 
 int C_RCV_HDR_OVF_FIRST ; 
 int C_RCV_HDR_OVF_LAST ; 
 struct cntr_entry* port_cntrs ; 
 int /*<<< orphan*/  read_dev_port_cntr (TYPE_1__*,struct cntr_entry*,int /*<<< orphan*/ *,struct hfi1_pportdata*,int) ; 

u64 read_port_cntr(struct hfi1_pportdata *ppd, int index, int vl)
{
	struct cntr_entry *entry;
	u64 *sval;

	entry = &port_cntrs[index];
	sval = ppd->scntrs + entry->offset;

	if (vl != CNTR_INVALID_VL)
		sval += vl;

	if ((index >= C_RCV_HDR_OVF_FIRST + ppd->dd->num_rcv_contexts) &&
	    (index <= C_RCV_HDR_OVF_LAST)) {
		/* We do not want to bother for disabled contexts */
		return 0;
	}

	return read_dev_port_cntr(ppd->dd, entry, sval, ppd, vl);
}