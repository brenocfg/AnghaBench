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

/* Variables and functions */
 scalar_t__ check_err (int) ; 
 int /*<<< orphan*/  devp_offset (void const*) ; 
 int /*<<< orphan*/  fdt ; 
 int fdt_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *fdt_wrapper_get_path(const void *devp, char *buf, int len)
{
	int rc;

	rc = fdt_get_path(fdt, devp_offset(devp), buf, len);
	if (check_err(rc))
		return NULL;
	return buf;
}