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
 int /*<<< orphan*/  CXL_PSL_SCNTL_An ; 
 unsigned long long cxl_p1n_read (struct cxl_afu*,int /*<<< orphan*/ ) ; 

int cxl_check_error(struct cxl_afu *afu)
{
	return (cxl_p1n_read(afu, CXL_PSL_SCNTL_An) == ~0ULL);
}