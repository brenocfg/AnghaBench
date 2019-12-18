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
typedef  int u64 ;
struct hfi1_devdata {int dummy; } ;
struct cntr_entry {int flags; int (* rw_cntr ) (struct cntr_entry*,void*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTR ; 
 int CNTR_32BIT ; 
 int CNTR_DISABLED ; 
 int /*<<< orphan*/  CNTR_MODE_W ; 
 int CNTR_SYNTH ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int stub1 (struct cntr_entry*,void*,int,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct cntr_entry*,void*,int,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct cntr_entry*,void*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 write_dev_port_cntr(struct hfi1_devdata *dd,
			       struct cntr_entry *entry,
			       u64 *psval, void *context, int vl, u64 data)
{
	u64 val;

	if (entry->flags & CNTR_DISABLED) {
		dd_dev_err(dd, "Counter %s not enabled", entry->name);
		return 0;
	}

	hfi1_cdbg(CNTR, "cntr: %s vl %d psval 0x%llx", entry->name, vl, *psval);

	if (entry->flags & CNTR_SYNTH) {
		*psval = data;
		if (entry->flags & CNTR_32BIT) {
			val = entry->rw_cntr(entry, context, vl, CNTR_MODE_W,
					     (data << 32) >> 32);
			val = data; /* return the full 64bit value */
		} else {
			val = entry->rw_cntr(entry, context, vl, CNTR_MODE_W,
					     data);
		}
	} else {
		val = entry->rw_cntr(entry, context, vl, CNTR_MODE_W, data);
	}

	*psval = val;

	hfi1_cdbg(CNTR, "\tNew val=0x%llx", val);

	return val;
}