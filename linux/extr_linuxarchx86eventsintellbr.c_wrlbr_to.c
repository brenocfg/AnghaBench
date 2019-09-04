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
struct TYPE_2__ {scalar_t__ lbr_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  wrmsrl (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static inline void wrlbr_to(unsigned int idx, u64 val)
{
	wrmsrl(x86_pmu.lbr_to + idx, val);
}