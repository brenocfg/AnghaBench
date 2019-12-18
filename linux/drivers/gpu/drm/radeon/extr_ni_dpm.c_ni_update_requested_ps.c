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
struct radeon_ps {struct ni_ps* ps_priv; } ;
struct radeon_device {int dummy; } ;
struct ni_ps {int dummy; } ;
struct ni_power_info {struct ni_ps requested_ps; } ;
struct evergreen_power_info {struct radeon_ps requested_rps; } ;

/* Variables and functions */
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 struct ni_ps* ni_get_ps (struct radeon_ps*) ; 

void ni_update_requested_ps(struct radeon_device *rdev,
			    struct radeon_ps *rps)
{
	struct ni_ps *new_ps = ni_get_ps(rps);
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);

	eg_pi->requested_rps = *rps;
	ni_pi->requested_ps = *new_ps;
	eg_pi->requested_rps.ps_priv = &ni_pi->requested_ps;
}