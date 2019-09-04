#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct radeon_vm {int dummy; } ;
struct radeon_fpriv {struct radeon_vm vm; } ;
struct radeon_device {scalar_t__ family; } ;
struct TYPE_4__ {int is_const_ib; int length_dw; int /*<<< orphan*/  ptr; } ;
struct radeon_cs_parser {int cs_flags; TYPE_2__ ib; int /*<<< orphan*/  ring; struct radeon_cs_chunk* chunk_ib; TYPE_2__ const_ib; struct radeon_cs_chunk* chunk_const_ib; TYPE_1__* filp; } ;
struct radeon_cs_chunk {int length_dw; int /*<<< orphan*/  user_ptr; scalar_t__ kdata; } ;
struct TYPE_3__ {struct radeon_fpriv* driver_priv; } ;

/* Variables and functions */
 scalar_t__ CHIP_TAHITI ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EFAULT ; 
 int EINVAL ; 
 int RADEON_CS_USE_VM ; 
 int RADEON_IB_VM_MAX_SIZE ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int radeon_ib_get (struct radeon_device*,int /*<<< orphan*/ ,TYPE_2__*,struct radeon_vm*,int) ; 

__attribute__((used)) static int radeon_cs_ib_fill(struct radeon_device *rdev, struct radeon_cs_parser *parser)
{
	struct radeon_cs_chunk *ib_chunk;
	struct radeon_vm *vm = NULL;
	int r;

	if (parser->chunk_ib == NULL)
		return 0;

	if (parser->cs_flags & RADEON_CS_USE_VM) {
		struct radeon_fpriv *fpriv = parser->filp->driver_priv;
		vm = &fpriv->vm;

		if ((rdev->family >= CHIP_TAHITI) &&
		    (parser->chunk_const_ib != NULL)) {
			ib_chunk = parser->chunk_const_ib;
			if (ib_chunk->length_dw > RADEON_IB_VM_MAX_SIZE) {
				DRM_ERROR("cs IB CONST too big: %d\n", ib_chunk->length_dw);
				return -EINVAL;
			}
			r =  radeon_ib_get(rdev, parser->ring, &parser->const_ib,
					   vm, ib_chunk->length_dw * 4);
			if (r) {
				DRM_ERROR("Failed to get const ib !\n");
				return r;
			}
			parser->const_ib.is_const_ib = true;
			parser->const_ib.length_dw = ib_chunk->length_dw;
			if (copy_from_user(parser->const_ib.ptr,
					       ib_chunk->user_ptr,
					       ib_chunk->length_dw * 4))
				return -EFAULT;
		}

		ib_chunk = parser->chunk_ib;
		if (ib_chunk->length_dw > RADEON_IB_VM_MAX_SIZE) {
			DRM_ERROR("cs IB too big: %d\n", ib_chunk->length_dw);
			return -EINVAL;
		}
	}
	ib_chunk = parser->chunk_ib;

	r =  radeon_ib_get(rdev, parser->ring, &parser->ib,
			   vm, ib_chunk->length_dw * 4);
	if (r) {
		DRM_ERROR("Failed to get ib !\n");
		return r;
	}
	parser->ib.length_dw = ib_chunk->length_dw;
	if (ib_chunk->kdata)
		memcpy(parser->ib.ptr, ib_chunk->kdata, ib_chunk->length_dw * 4);
	else if (copy_from_user(parser->ib.ptr, ib_chunk->user_ptr, ib_chunk->length_dw * 4))
		return -EFAULT;
	return 0;
}