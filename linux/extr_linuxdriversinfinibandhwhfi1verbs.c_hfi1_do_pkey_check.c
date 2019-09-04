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
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_packet {scalar_t__ etype; int /*<<< orphan*/  slid; TYPE_1__* qp; int /*<<< orphan*/  sc; struct hfi1_16b_header* hdr; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_ctxtdata {struct hfi1_pportdata* ppd; } ;
struct hfi1_16b_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_pkey_index; } ;

/* Variables and functions */
 scalar_t__ RHF_RCV_TYPE_BYPASS ; 
 int /*<<< orphan*/  hfi1_16B_get_pkey (struct hfi1_16b_header*) ; 
 int ingress_pkey_check (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hfi1_do_pkey_check(struct hfi1_packet *packet)
{
	struct hfi1_ctxtdata *rcd = packet->rcd;
	struct hfi1_pportdata *ppd = rcd->ppd;
	struct hfi1_16b_header *hdr = packet->hdr;
	u16 pkey;

	/* Pkey check needed only for bypass packets */
	if (packet->etype != RHF_RCV_TYPE_BYPASS)
		return 0;

	/* Perform pkey check */
	pkey = hfi1_16B_get_pkey(hdr);
	return ingress_pkey_check(ppd, pkey, packet->sc,
				  packet->qp->s_pkey_index,
				  packet->slid, true);
}