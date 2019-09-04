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
struct resource_caps {int dummy; } ;
struct hw_asic_id {int /*<<< orphan*/  hw_internal_rev; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_IS_STONEY (int /*<<< orphan*/ ) ; 
 struct resource_caps const carrizo_resource_cap ; 
 struct resource_caps const stoney_resource_cap ; 

const struct resource_caps *dce110_resource_cap(
	struct hw_asic_id *asic_id)
{
	if (ASIC_REV_IS_STONEY(asic_id->hw_internal_rev))
		return &stoney_resource_cap;
	else
		return &carrizo_resource_cap;
}