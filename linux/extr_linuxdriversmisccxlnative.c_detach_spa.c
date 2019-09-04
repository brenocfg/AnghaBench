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
 int /*<<< orphan*/  CXL_PSL_SPAP_An ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void detach_spa(struct cxl_afu *afu)
{
	cxl_p1n_write(afu, CXL_PSL_SPAP_An, 0);
}