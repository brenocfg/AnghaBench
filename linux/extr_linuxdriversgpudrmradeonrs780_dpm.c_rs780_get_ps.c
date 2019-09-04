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
struct radeon_ps {struct igp_ps* ps_priv; } ;
struct igp_ps {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct igp_ps *rs780_get_ps(struct radeon_ps *rps)
{
	struct igp_ps *ps = rps->ps_priv;

	return ps;
}