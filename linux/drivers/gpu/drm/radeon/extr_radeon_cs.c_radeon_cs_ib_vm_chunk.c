#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct radeon_vm {int /*<<< orphan*/  mutex; } ;
struct radeon_fpriv {struct radeon_vm vm; } ;
struct radeon_device {scalar_t__ family; } ;
struct TYPE_6__ {scalar_t__ length_dw; } ;
struct radeon_cs_parser {int cs_flags; scalar_t__ ring; TYPE_2__ ib; TYPE_2__ const_ib; int /*<<< orphan*/ * chunk_const_ib; int /*<<< orphan*/ * chunk_ib; TYPE_1__* filp; } ;
struct TYPE_5__ {struct radeon_fpriv* driver_priv; } ;

/* Variables and functions */
 scalar_t__ CHIP_TAHITI ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int ERESTARTSYS ; 
 scalar_t__ R600_RING_TYPE_UVD_INDEX ; 
 int RADEON_CS_USE_VM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_bo_vm_update_pte (struct radeon_cs_parser*,struct radeon_vm*) ; 
 int radeon_cs_sync_rings (struct radeon_cs_parser*) ; 
 int radeon_ib_schedule (struct radeon_device*,TYPE_2__*,TYPE_2__*,int) ; 
 int radeon_ring_ib_parse (struct radeon_device*,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  radeon_uvd_note_usage (struct radeon_device*) ; 

__attribute__((used)) static int radeon_cs_ib_vm_chunk(struct radeon_device *rdev,
				 struct radeon_cs_parser *parser)
{
	struct radeon_fpriv *fpriv = parser->filp->driver_priv;
	struct radeon_vm *vm = &fpriv->vm;
	int r;

	if (parser->chunk_ib == NULL)
		return 0;
	if ((parser->cs_flags & RADEON_CS_USE_VM) == 0)
		return 0;

	if (parser->const_ib.length_dw) {
		r = radeon_ring_ib_parse(rdev, parser->ring, &parser->const_ib);
		if (r) {
			return r;
		}
	}

	r = radeon_ring_ib_parse(rdev, parser->ring, &parser->ib);
	if (r) {
		return r;
	}

	if (parser->ring == R600_RING_TYPE_UVD_INDEX)
		radeon_uvd_note_usage(rdev);

	mutex_lock(&vm->mutex);
	r = radeon_bo_vm_update_pte(parser, vm);
	if (r) {
		goto out;
	}

	r = radeon_cs_sync_rings(parser);
	if (r) {
		if (r != -ERESTARTSYS)
			DRM_ERROR("Failed to sync rings: %i\n", r);
		goto out;
	}

	if ((rdev->family >= CHIP_TAHITI) &&
	    (parser->chunk_const_ib != NULL)) {
		r = radeon_ib_schedule(rdev, &parser->ib, &parser->const_ib, true);
	} else {
		r = radeon_ib_schedule(rdev, &parser->ib, NULL, true);
	}

out:
	mutex_unlock(&vm->mutex);
	return r;
}