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
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_AFU_Cntl_An_E ; 
 int /*<<< orphan*/  CXL_AFU_Cntl_An_ES_Disabled ; 
 int /*<<< orphan*/  CXL_AFU_Cntl_An_ES_MASK ; 
 int afu_control (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 

int cxl_afu_disable(struct cxl_afu *afu)
{
	pr_devel("AFU disable request\n");

	return afu_control(afu, 0, CXL_AFU_Cntl_An_E,
			   CXL_AFU_Cntl_An_ES_Disabled,
			   CXL_AFU_Cntl_An_ES_MASK, false);
}