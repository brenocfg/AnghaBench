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
typedef  enum cxl_attrs { ____Placeholder_cxl_attrs } cxl_attrs ;

/* Variables and functions */

__attribute__((used)) static bool native_support_attributes(const char *attr_name,
				      enum cxl_attrs type)
{
	return true;
}