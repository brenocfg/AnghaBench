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
typedef  int u32 ;
struct owl_pingroup {int nfuncs; int* funcs; int mfpctl_width; int mfpctl_shift; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static inline int get_group_mfp_mask_val(const struct owl_pingroup *g,
				int function,
				u32 *mask,
				u32 *val)
{
	int id;
	u32 option_num;
	u32 option_mask;

	for (id = 0; id < g->nfuncs; id++) {
		if (g->funcs[id] == function)
			break;
	}
	if (WARN_ON(id == g->nfuncs))
		return -EINVAL;

	option_num = (1 << g->mfpctl_width);
	if (id > option_num)
		id -= option_num;

	option_mask = option_num - 1;
	*mask = (option_mask  << g->mfpctl_shift);
	*val = (id << g->mfpctl_shift);

	return 0;
}