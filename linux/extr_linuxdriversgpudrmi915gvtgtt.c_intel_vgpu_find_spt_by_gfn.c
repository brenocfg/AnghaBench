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
struct intel_vgpu_ppgtt_spt {int dummy; } ;
struct intel_vgpu_page_track {scalar_t__ handler; struct intel_vgpu_ppgtt_spt* priv_data; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 struct intel_vgpu_page_track* intel_vgpu_find_page_track (struct intel_vgpu*,unsigned long) ; 
 scalar_t__ ppgtt_write_protection_handler ; 

__attribute__((used)) static struct intel_vgpu_ppgtt_spt *intel_vgpu_find_spt_by_gfn(
		struct intel_vgpu *vgpu, unsigned long gfn)
{
	struct intel_vgpu_page_track *track;

	track = intel_vgpu_find_page_track(vgpu, gfn);
	if (track && track->handler == ppgtt_write_protection_handler)
		return track->priv_data;

	return NULL;
}