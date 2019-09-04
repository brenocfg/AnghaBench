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
struct stm_fs {int dummy; } ;
struct st_clk_quadfs_fsynth {int dummy; } ;
struct clk_hw {int dummy; } ;
typedef  int /*<<< orphan*/  i ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct stm_fs*,int /*<<< orphan*/ ,int) ; 
 long quadfs_find_best_rate (struct clk_hw*,unsigned long,unsigned long,struct stm_fs*) ; 
 int /*<<< orphan*/  quadfs_program_and_enable (struct st_clk_quadfs_fsynth*,struct stm_fs*) ; 
 struct st_clk_quadfs_fsynth* to_quadfs_fsynth (struct clk_hw*) ; 

__attribute__((used)) static int quadfs_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	struct st_clk_quadfs_fsynth *fs = to_quadfs_fsynth(hw);
	struct stm_fs params;
	long hwrate;
	int uninitialized_var(i);

	if (!rate || !parent_rate)
		return -EINVAL;

	memset(&params, 0, sizeof(struct stm_fs));

	hwrate = quadfs_find_best_rate(hw, rate, parent_rate, &params);
	if (!hwrate)
		return -EINVAL;

	quadfs_program_and_enable(fs, &params);

	return 0;
}