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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cik_enable_gfx_cgpg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_gfx_dynamic_mgpg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_gfx_static_mgpg (struct radeon_device*,int) ; 

__attribute__((used)) static void cik_update_gfx_pg(struct radeon_device *rdev, bool enable)
{
	cik_enable_gfx_cgpg(rdev, enable);
	cik_enable_gfx_static_mgpg(rdev, enable);
	cik_enable_gfx_dynamic_mgpg(rdev, enable);
}