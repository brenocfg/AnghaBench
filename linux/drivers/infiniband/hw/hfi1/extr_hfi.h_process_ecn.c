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
struct rvt_qp {int dummy; } ;
struct hfi1_packet {int dummy; } ;

/* Variables and functions */
 int hfi1_may_ecn (struct hfi1_packet*) ; 
 int hfi1_process_ecn_slowpath (struct rvt_qp*,struct hfi1_packet*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool process_ecn(struct rvt_qp *qp, struct hfi1_packet *pkt)
{
	bool do_work;

	do_work = hfi1_may_ecn(pkt);
	if (unlikely(do_work))
		return hfi1_process_ecn_slowpath(qp, pkt, false);
	return false;
}