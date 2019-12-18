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
struct max2175 {int dummy; } ;
typedef  enum max2175_csm_mode { ____Placeholder_max2175_csm_mode } max2175_csm_mode ;

/* Variables and functions */
 int /*<<< orphan*/  MAX2175_LOAD_TO_BUFFER ; 
 int /*<<< orphan*/  MAX2175_PRESET_TUNE ; 
 int max2175_set_csm_mode (struct max2175*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxm_dbg (struct max2175*,char*,int) ; 

__attribute__((used)) static int max2175_csm_action(struct max2175 *ctx,
			      enum max2175_csm_mode action)
{
	int ret;

	mxm_dbg(ctx, "csm_action: %d\n", action);

	/* Other actions can be added in future when needed */
	ret = max2175_set_csm_mode(ctx, MAX2175_LOAD_TO_BUFFER);
	if (ret)
		return ret;

	return max2175_set_csm_mode(ctx, MAX2175_PRESET_TUNE);
}