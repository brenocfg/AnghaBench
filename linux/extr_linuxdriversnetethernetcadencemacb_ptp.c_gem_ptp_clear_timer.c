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
struct TYPE_2__ {scalar_t__ ns; scalar_t__ sub_ns; } ;
struct macb {TYPE_1__ tsu_incr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSINCR ; 
 int /*<<< orphan*/  SUBNSINCR ; 
 int /*<<< orphan*/  TA ; 
 int /*<<< orphan*/  TI ; 
 int /*<<< orphan*/  TISUBN ; 
 int /*<<< orphan*/  gem_writel (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gem_ptp_clear_timer(struct macb *bp)
{
	bp->tsu_incr.sub_ns = 0;
	bp->tsu_incr.ns = 0;

	gem_writel(bp, TISUBN, GEM_BF(SUBNSINCR, 0));
	gem_writel(bp, TI, GEM_BF(NSINCR, 0));
	gem_writel(bp, TA, 0);
}