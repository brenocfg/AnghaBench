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
struct intel_gvt {int dummy; } ;

/* Variables and functions */
 int init_cmd_table (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_gvt_clean_cmd_parser (struct intel_gvt*) ; 

int intel_gvt_init_cmd_parser(struct intel_gvt *gvt)
{
	int ret;

	ret = init_cmd_table(gvt);
	if (ret) {
		intel_gvt_clean_cmd_parser(gvt);
		return ret;
	}
	return 0;
}