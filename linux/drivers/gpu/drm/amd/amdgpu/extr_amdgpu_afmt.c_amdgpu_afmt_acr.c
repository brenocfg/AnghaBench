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
typedef  scalar_t__ uint32_t ;
typedef  size_t u8 ;
struct amdgpu_afmt_acr {scalar_t__ clock; int /*<<< orphan*/  n_48khz; int /*<<< orphan*/  cts_48khz; int /*<<< orphan*/  n_44_1khz; int /*<<< orphan*/  cts_44_1khz; int /*<<< orphan*/  n_32khz; int /*<<< orphan*/  cts_32khz; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct amdgpu_afmt_acr*) ; 
 int /*<<< orphan*/  amdgpu_afmt_calc_cts (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct amdgpu_afmt_acr* amdgpu_afmt_predefined_acr ; 

struct amdgpu_afmt_acr amdgpu_afmt_acr(uint32_t clock)
{
	struct amdgpu_afmt_acr res;
	u8 i;

	/* Precalculated values for common clocks */
	for (i = 0; i < ARRAY_SIZE(amdgpu_afmt_predefined_acr); i++) {
		if (amdgpu_afmt_predefined_acr[i].clock == clock)
			return amdgpu_afmt_predefined_acr[i];
	}

	/* And odd clocks get manually calculated */
	amdgpu_afmt_calc_cts(clock, &res.cts_32khz, &res.n_32khz, 32000);
	amdgpu_afmt_calc_cts(clock, &res.cts_44_1khz, &res.n_44_1khz, 44100);
	amdgpu_afmt_calc_cts(clock, &res.cts_48khz, &res.n_48khz, 48000);

	return res;
}