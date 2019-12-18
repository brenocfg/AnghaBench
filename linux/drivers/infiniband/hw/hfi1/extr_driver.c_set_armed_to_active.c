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
typedef  scalar_t__ u8 ;
struct work_struct {int dummy; } ;
struct ib_header {int dummy; } ;
struct hfi1_packet {int /*<<< orphan*/  rhf_addr; int /*<<< orphan*/  rcd; int /*<<< orphan*/  rhf; } ;
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {TYPE_1__* ppd; } ;
struct hfi1_16b_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  link_wq; struct work_struct linkstate_active_work; } ;

/* Variables and functions */
 int IB_PORT_ACTIVE ; 
 scalar_t__ RHF_RCV_TYPE_BYPASS ; 
 scalar_t__ RHF_RCV_TYPE_IB ; 
 scalar_t__ SC15_PACKET ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int driver_lstate (TYPE_1__*) ; 
 scalar_t__ hfi1_16B_get_sc (struct hfi1_16b_header*) ; 
 scalar_t__ hfi1_9B_get_sc5 (struct ib_header*,int /*<<< orphan*/ ) ; 
 struct hfi1_16b_header* hfi1_get_16B_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ib_header* hfi1_get_msgheader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_lstate_name (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 scalar_t__ rhf_rcv_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int set_armed_to_active(struct hfi1_ctxtdata *rcd,
				      struct hfi1_packet *packet,
				      struct hfi1_devdata *dd)
{
	struct work_struct *lsaw = &rcd->ppd->linkstate_active_work;
	u8 etype = rhf_rcv_type(packet->rhf);
	u8 sc = SC15_PACKET;

	if (etype == RHF_RCV_TYPE_IB) {
		struct ib_header *hdr = hfi1_get_msgheader(packet->rcd,
							   packet->rhf_addr);
		sc = hfi1_9B_get_sc5(hdr, packet->rhf);
	} else if (etype == RHF_RCV_TYPE_BYPASS) {
		struct hfi1_16b_header *hdr = hfi1_get_16B_header(
						packet->rcd,
						packet->rhf_addr);
		sc = hfi1_16B_get_sc(hdr);
	}
	if (sc != SC15_PACKET) {
		int hwstate = driver_lstate(rcd->ppd);

		if (hwstate != IB_PORT_ACTIVE) {
			dd_dev_info(dd,
				    "Unexpected link state %s\n",
				    opa_lstate_name(hwstate));
			return 0;
		}

		queue_work(rcd->ppd->link_wq, lsaw);
		return 1;
	}
	return 0;
}