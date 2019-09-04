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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sub_ns; int /*<<< orphan*/  ns; } ;
struct macb {TYPE_1__ tsu_incr; int /*<<< orphan*/  tsu_rate; } ;

/* Variables and functions */
 scalar_t__ GEM_SUBNSINCR_SIZE ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  div_u64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64_rem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void gem_ptp_init_timer(struct macb *bp)
{
	u32 rem = 0;
	u64 adj;

	bp->tsu_incr.ns = div_u64_rem(NSEC_PER_SEC, bp->tsu_rate, &rem);
	if (rem) {
		adj = rem;
		adj <<= GEM_SUBNSINCR_SIZE;
		bp->tsu_incr.sub_ns = div_u64(adj, bp->tsu_rate);
	} else {
		bp->tsu_incr.sub_ns = 0;
	}
}