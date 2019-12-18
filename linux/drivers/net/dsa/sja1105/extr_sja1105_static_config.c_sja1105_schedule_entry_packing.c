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
struct sja1105_schedule_entry {int /*<<< orphan*/  delta; int /*<<< orphan*/  vlindex; int /*<<< orphan*/  resmedia; int /*<<< orphan*/  resmedia_en; int /*<<< orphan*/  txen; int /*<<< orphan*/  setvalid; int /*<<< orphan*/  destports; int /*<<< orphan*/  winst; int /*<<< orphan*/  winend; int /*<<< orphan*/  winstindex; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 size_t SJA1105_SIZE_SCHEDULE_ENTRY ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,size_t const,int) ; 

__attribute__((used)) static size_t sja1105_schedule_entry_packing(void *buf, void *entry_ptr,
					     enum packing_op op)
{
	const size_t size = SJA1105_SIZE_SCHEDULE_ENTRY;
	struct sja1105_schedule_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->winstindex,  63, 54, size, op);
	sja1105_packing(buf, &entry->winend,      53, 53, size, op);
	sja1105_packing(buf, &entry->winst,       52, 52, size, op);
	sja1105_packing(buf, &entry->destports,   51, 47, size, op);
	sja1105_packing(buf, &entry->setvalid,    46, 46, size, op);
	sja1105_packing(buf, &entry->txen,        45, 45, size, op);
	sja1105_packing(buf, &entry->resmedia_en, 44, 44, size, op);
	sja1105_packing(buf, &entry->resmedia,    43, 36, size, op);
	sja1105_packing(buf, &entry->vlindex,     35, 26, size, op);
	sja1105_packing(buf, &entry->delta,       25, 8,  size, op);
	return size;
}