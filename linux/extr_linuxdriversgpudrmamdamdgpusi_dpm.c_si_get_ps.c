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
struct si_ps {int dummy; } ;
struct amdgpu_ps {struct si_ps* ps_priv; } ;

/* Variables and functions */

__attribute__((used)) static struct si_ps *si_get_ps(struct amdgpu_ps *aps)
{
	struct  si_ps *ps = aps->ps_priv;

	return ps;
}