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
typedef  int /*<<< orphan*/  u64 ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SCD_ZBBUS_CYCLE_COUNT ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_readq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 bcm1480_hpt_read(struct clocksource *cs)
{
	return (u64) __raw_readq(IOADDR(A_SCD_ZBBUS_CYCLE_COUNT));
}