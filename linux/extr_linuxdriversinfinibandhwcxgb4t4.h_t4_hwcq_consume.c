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
typedef  int u32 ;
struct t4_cq {size_t cidx; int cidx_inc; int size; int gen; TYPE_1__* queue; int /*<<< orphan*/  bits_type_ts; } ;
struct TYPE_2__ {int /*<<< orphan*/  bits_type_ts; } ;

/* Variables and functions */
 int CIDXINC_M ; 
 int CIDXINC_V (int) ; 
 int SEINTARM_V (int /*<<< orphan*/ ) ; 
 int TIMERREG_V (int) ; 
 int /*<<< orphan*/  write_gts (struct t4_cq*,int) ; 

__attribute__((used)) static inline void t4_hwcq_consume(struct t4_cq *cq)
{
	cq->bits_type_ts = cq->queue[cq->cidx].bits_type_ts;
	if (++cq->cidx_inc == (cq->size >> 4) || cq->cidx_inc == CIDXINC_M) {
		u32 val;

		val = SEINTARM_V(0) | CIDXINC_V(cq->cidx_inc) | TIMERREG_V(7);
		write_gts(cq, val);
		cq->cidx_inc = 0;
	}
	if (++cq->cidx == cq->size) {
		cq->cidx = 0;
		cq->gen ^= 1;
	}
}