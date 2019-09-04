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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  XTENSA_PMU_PM (int) ; 
 int /*<<< orphan*/  get_er (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t xtensa_pmu_read_counter(int idx)
{
	return get_er(XTENSA_PMU_PM(idx));
}