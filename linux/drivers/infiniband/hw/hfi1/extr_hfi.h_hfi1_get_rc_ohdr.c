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
typedef  scalar_t__ u8 ;
struct ib_other_headers {int dummy; } ;
struct TYPE_5__ {struct ib_other_headers oth; } ;
struct TYPE_6__ {TYPE_1__ l; struct ib_other_headers oth; } ;
struct ib_header {TYPE_2__ u; } ;
struct TYPE_7__ {struct ib_other_headers oth; } ;
struct TYPE_8__ {TYPE_3__ l; struct ib_other_headers oth; } ;
struct hfi1_16b_header {TYPE_4__ u; } ;
struct hfi1_opa_header {scalar_t__ hdr_type; struct hfi1_16b_header opah; struct ib_header ibh; } ;

/* Variables and functions */
 scalar_t__ HFI1_LRH_BTH ; 
 scalar_t__ HFI1_PKT_TYPE_9B ; 
 scalar_t__ OPA_16B_L4_IB_LOCAL ; 
 scalar_t__ hfi1_16B_get_l4 (struct hfi1_16b_header*) ; 
 scalar_t__ ib_get_lnh (struct ib_header*) ; 

__attribute__((used)) static inline struct ib_other_headers *
hfi1_get_rc_ohdr(struct hfi1_opa_header *opah)
{
	struct ib_other_headers *ohdr;
	struct ib_header *hdr = NULL;
	struct hfi1_16b_header *hdr_16b = NULL;

	/* Find out where the BTH is */
	if (opah->hdr_type == HFI1_PKT_TYPE_9B) {
		hdr = &opah->ibh;
		if (ib_get_lnh(hdr) == HFI1_LRH_BTH)
			ohdr = &hdr->u.oth;
		else
			ohdr = &hdr->u.l.oth;
	} else {
		u8 l4;

		hdr_16b = &opah->opah;
		l4  = hfi1_16B_get_l4(hdr_16b);
		if (l4 == OPA_16B_L4_IB_LOCAL)
			ohdr = &hdr_16b->u.oth;
		else
			ohdr = &hdr_16b->u.l.oth;
	}
	return ohdr;
}