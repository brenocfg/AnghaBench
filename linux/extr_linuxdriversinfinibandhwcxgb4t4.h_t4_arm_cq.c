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
typedef  int u32 ;
struct t4_cq {scalar_t__ cidx_inc; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CIDXINC_M ; 
 int CIDXINC_V (scalar_t__) ; 
 int /*<<< orphan*/  CQ_ARMED ; 
 int SEINTARM_V (int) ; 
 int TIMERREG_V (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_gts (struct t4_cq*,int) ; 

__attribute__((used)) static inline int t4_arm_cq(struct t4_cq *cq, int se)
{
	u32 val;

	set_bit(CQ_ARMED, &cq->flags);
	while (cq->cidx_inc > CIDXINC_M) {
		val = SEINTARM_V(0) | CIDXINC_V(CIDXINC_M) | TIMERREG_V(7);
		write_gts(cq, val);
		cq->cidx_inc -= CIDXINC_M;
	}
	val = SEINTARM_V(se) | CIDXINC_V(cq->cidx_inc) | TIMERREG_V(6);
	write_gts(cq, val);
	cq->cidx_inc = 0;
	return 0;
}