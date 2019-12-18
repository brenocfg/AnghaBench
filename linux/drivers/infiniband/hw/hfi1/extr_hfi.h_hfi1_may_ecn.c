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
struct hfi1_packet {scalar_t__ etype; int /*<<< orphan*/  ohdr; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 scalar_t__ RHF_RCV_TYPE_BYPASS ; 
 int hfi1_16B_get_becn (int /*<<< orphan*/ ) ; 
 int hfi1_16B_get_fecn (int /*<<< orphan*/ ) ; 
 int ib_bth_get_becn (int /*<<< orphan*/ ) ; 
 int ib_bth_get_fecn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool hfi1_may_ecn(struct hfi1_packet *pkt)
{
	bool fecn, becn;

	if (pkt->etype == RHF_RCV_TYPE_BYPASS) {
		fecn = hfi1_16B_get_fecn(pkt->hdr);
		becn = hfi1_16B_get_becn(pkt->hdr);
	} else {
		fecn = ib_bth_get_fecn(pkt->ohdr);
		becn = ib_bth_get_becn(pkt->ohdr);
	}
	return fecn || becn;
}