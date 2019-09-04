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
struct f54_data {int* inputs; } ;
typedef  enum rmi_f54_report_type { ____Placeholder_rmi_f54_report_type } rmi_f54_report_type ;

/* Variables and functions */
 int F54_MAX_REPORT_TYPE ; 
 int /*<<< orphan*/  is_f54_report_type_valid (struct f54_data*,int) ; 

__attribute__((used)) static void rmi_f54_create_input_map(struct f54_data *f54)
{
	int i = 0;
	enum rmi_f54_report_type reptype;

	for (reptype = 1; reptype < F54_MAX_REPORT_TYPE; reptype++) {
		if (!is_f54_report_type_valid(f54, reptype))
			continue;

		f54->inputs[i++] = reptype;
	}

	/* Remaining values are zero via kzalloc */
}