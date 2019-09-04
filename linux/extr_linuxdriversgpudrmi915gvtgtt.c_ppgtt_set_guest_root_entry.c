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
struct intel_vgpu_mm {int dummy; } ;
struct intel_gvt_gtt_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ppgtt_set_root_entry (struct intel_vgpu_mm*,struct intel_gvt_gtt_entry*,unsigned long,int) ; 

__attribute__((used)) static inline void ppgtt_set_guest_root_entry(struct intel_vgpu_mm *mm,
		struct intel_gvt_gtt_entry *entry, unsigned long index)
{
	_ppgtt_set_root_entry(mm, entry, index, true);
}