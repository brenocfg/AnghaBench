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
struct cxl {int caia_major; } ;

/* Variables and functions */
 scalar_t__ cxl_is_power8 () ; 
 scalar_t__ cxl_is_power9 () ; 

__attribute__((used)) static bool cxl_compatible_caia_version(struct cxl *adapter)
{
	if (cxl_is_power8() && (adapter->caia_major == 1))
		return true;

	if (cxl_is_power9() && (adapter->caia_major == 2))
		return true;

	return false;
}