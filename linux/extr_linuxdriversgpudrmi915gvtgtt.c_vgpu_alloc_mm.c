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
struct intel_vgpu_mm {int /*<<< orphan*/  pincount; int /*<<< orphan*/  ref; struct intel_vgpu* vgpu; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct intel_vgpu_mm* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_vgpu_mm *vgpu_alloc_mm(struct intel_vgpu *vgpu)
{
	struct intel_vgpu_mm *mm;

	mm = kzalloc(sizeof(*mm), GFP_KERNEL);
	if (!mm)
		return NULL;

	mm->vgpu = vgpu;
	kref_init(&mm->ref);
	atomic_set(&mm->pincount, 0);

	return mm;
}