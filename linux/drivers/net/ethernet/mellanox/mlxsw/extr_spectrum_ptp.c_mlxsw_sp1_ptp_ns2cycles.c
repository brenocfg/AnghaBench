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
typedef  int /*<<< orphan*/  u64 ;
struct timecounter {TYPE_1__* cc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mult; int /*<<< orphan*/  shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 mlxsw_sp1_ptp_ns2cycles(const struct timecounter *tc, u64 nsec)
{
	u64 cycles = (u64) nsec;

	cycles <<= tc->cc->shift;
	cycles = div_u64(cycles, tc->cc->mult);

	return cycles;
}