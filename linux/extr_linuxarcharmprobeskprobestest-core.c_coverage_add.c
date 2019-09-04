#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bits; } ;
struct TYPE_6__ {int bits; } ;
struct TYPE_5__ {int bits; } ;
struct decode_header {TYPE_3__ value; TYPE_2__ mask; TYPE_1__ type_regs; } ;
struct coverage_entry {unsigned int nesting; int matched; struct decode_header* header; } ;
typedef  int kprobe_opcode_t ;
typedef  enum decode_type { ____Placeholder_decode_type } decode_type ;
struct TYPE_8__ {int num_entries; struct coverage_entry* base; } ;

/* Variables and functions */
#define  DECODE_TYPE_CUSTOM 133 
#define  DECODE_TYPE_EMULATE 132 
 int DECODE_TYPE_MASK ; 
#define  DECODE_TYPE_OR 131 
#define  DECODE_TYPE_REJECT 130 
#define  DECODE_TYPE_SIMULATE 129 
#define  DECODE_TYPE_TABLE 128 
 TYPE_4__ coverage ; 
 int /*<<< orphan*/  coverage_add_registers (struct coverage_entry*,int) ; 

__attribute__((used)) static void coverage_add(kprobe_opcode_t insn)
{
	struct coverage_entry *entry = coverage.base;
	struct coverage_entry *end = coverage.base + coverage.num_entries;
	bool matched = false;
	unsigned nesting = 0;

	for (; entry < end; ++entry) {
		const struct decode_header *h = entry->header;
		enum decode_type type = h->type_regs.bits & DECODE_TYPE_MASK;

		if (entry->nesting > nesting)
			continue; /* Skip sub-table we didn't match */

		if (entry->nesting < nesting)
			break; /* End of sub-table we were scanning */

		if (!matched) {
			if ((insn & h->mask.bits) != h->value.bits)
				continue;
			entry->matched = true;
		}

		switch (type) {

		case DECODE_TYPE_TABLE:
			++nesting;
			break;

		case DECODE_TYPE_CUSTOM:
		case DECODE_TYPE_SIMULATE:
		case DECODE_TYPE_EMULATE:
			coverage_add_registers(entry, insn);
			return;

		case DECODE_TYPE_OR:
			matched = true;
			break;

		case DECODE_TYPE_REJECT:
		default:
			return;
		}

	}
}