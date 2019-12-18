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
struct tegra_pmc {int /*<<< orphan*/  powergates_available; } ;

/* Variables and functions */
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool tegra_powergate_is_available(struct tegra_pmc *pmc, int id)
{
	return test_bit(id, pmc->powergates_available);
}