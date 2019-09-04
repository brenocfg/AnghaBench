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
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_devdata {int /*<<< orphan*/ * scntrs; } ;
struct cntr_entry {int offset; } ;

/* Variables and functions */
 int CNTR_INVALID_VL ; 
 struct cntr_entry* dev_cntrs ; 
 int /*<<< orphan*/  read_dev_port_cntr (struct hfi1_devdata*,struct cntr_entry*,int /*<<< orphan*/ *,struct hfi1_devdata*,int) ; 

u64 read_dev_cntr(struct hfi1_devdata *dd, int index, int vl)
{
	struct cntr_entry *entry;
	u64 *sval;

	entry = &dev_cntrs[index];
	sval = dd->scntrs + entry->offset;

	if (vl != CNTR_INVALID_VL)
		sval += vl;

	return read_dev_port_cntr(dd, entry, sval, dd, vl);
}