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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ XIVE_INVALID_VP ; 
 scalar_t__ opal_xive_free_vp_block (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 

void xive_native_free_vp_block(u32 vp_base)
{
	s64 rc;

	if (vp_base == XIVE_INVALID_VP)
		return;

	rc = opal_xive_free_vp_block(vp_base);
	if (rc < 0)
		pr_warn("OPAL error %lld freeing VP block\n", rc);
}