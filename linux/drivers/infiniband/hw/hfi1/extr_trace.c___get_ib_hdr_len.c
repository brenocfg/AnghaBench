#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ib_other_headers {int dummy; } ;
struct TYPE_3__ {struct ib_other_headers oth; } ;
struct TYPE_4__ {TYPE_1__ l; struct ib_other_headers oth; } ;
struct ib_header {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ HFI1_LRH_BTH ; 
 int* hdr_len_by_opcode ; 
 size_t ib_bth_get_opcode (struct ib_other_headers*) ; 
 scalar_t__ ib_get_lnh (struct ib_header*) ; 

__attribute__((used)) static u8 __get_ib_hdr_len(struct ib_header *hdr)
{
	struct ib_other_headers *ohdr;
	u8 opcode;

	if (ib_get_lnh(hdr) == HFI1_LRH_BTH)
		ohdr = &hdr->u.oth;
	else
		ohdr = &hdr->u.l.oth;
	opcode = ib_bth_get_opcode(ohdr);
	return hdr_len_by_opcode[opcode] == 0 ?
	       0 : hdr_len_by_opcode[opcode] - (12 + 8);
}