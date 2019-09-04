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
struct hi6220_stub_clk {int /*<<< orphan*/  dfs_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPU_DFS_CUR_FREQ ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int hi6220_acpu_get_freq(struct hi6220_stub_clk *stub_clk)
{
	unsigned int freq;

	regmap_read(stub_clk->dfs_map, ACPU_DFS_CUR_FREQ, &freq);
	return freq;
}