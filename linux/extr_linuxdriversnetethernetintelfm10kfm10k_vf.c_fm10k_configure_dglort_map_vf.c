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
struct fm10k_hw {int dummy; } ;
struct fm10k_dglort_cfg {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 

__attribute__((used)) static s32 fm10k_configure_dglort_map_vf(struct fm10k_hw *hw,
					 struct fm10k_dglort_cfg *dglort)
{
	/* verify the dglort pointer */
	if (!dglort)
		return FM10K_ERR_PARAM;

	/* stub for now until we determine correct message for this */

	return 0;
}