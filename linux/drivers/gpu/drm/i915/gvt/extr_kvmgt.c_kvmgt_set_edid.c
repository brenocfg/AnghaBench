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
struct TYPE_3__ {int /*<<< orphan*/  max_yres; int /*<<< orphan*/  max_xres; void* edid_size; void* edid_max_size; int /*<<< orphan*/  edid_offset; } ;
struct vfio_edid_region {int /*<<< orphan*/  edid_blob; TYPE_1__ vfio_edid_regs; } ;
struct intel_vgpu_port {TYPE_2__* edid; int /*<<< orphan*/  id; } ;
struct intel_vgpu {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  edid_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDID_BLOB_OFFSET ; 
 void* EDID_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VFIO_REGION_INFO_FLAG_CAPS ; 
 int VFIO_REGION_INFO_FLAG_READ ; 
 int VFIO_REGION_INFO_FLAG_WRITE ; 
 int /*<<< orphan*/  VFIO_REGION_SUBTYPE_GFX_EDID ; 
 int /*<<< orphan*/  VFIO_REGION_TYPE_GFX ; 
 struct intel_vgpu_port* intel_vgpu_port (struct intel_vgpu*,int) ; 
 int intel_vgpu_register_reg (struct intel_vgpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int,struct vfio_edid_region*) ; 
 int /*<<< orphan*/  intel_vgpu_regops_edid ; 
 struct vfio_edid_region* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgpu_edid_xres (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vgpu_edid_yres (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmgt_set_edid(void *p_vgpu, int port_num)
{
	struct intel_vgpu *vgpu = (struct intel_vgpu *)p_vgpu;
	struct intel_vgpu_port *port = intel_vgpu_port(vgpu, port_num);
	struct vfio_edid_region *base;
	int ret;

	base = kzalloc(sizeof(*base), GFP_KERNEL);
	if (!base)
		return -ENOMEM;

	/* TODO: Add multi-port and EDID extension block support */
	base->vfio_edid_regs.edid_offset = EDID_BLOB_OFFSET;
	base->vfio_edid_regs.edid_max_size = EDID_SIZE;
	base->vfio_edid_regs.edid_size = EDID_SIZE;
	base->vfio_edid_regs.max_xres = vgpu_edid_xres(port->id);
	base->vfio_edid_regs.max_yres = vgpu_edid_yres(port->id);
	base->edid_blob = port->edid->edid_block;

	ret = intel_vgpu_register_reg(vgpu,
			VFIO_REGION_TYPE_GFX,
			VFIO_REGION_SUBTYPE_GFX_EDID,
			&intel_vgpu_regops_edid, EDID_SIZE,
			VFIO_REGION_INFO_FLAG_READ |
			VFIO_REGION_INFO_FLAG_WRITE |
			VFIO_REGION_INFO_FLAG_CAPS, base);

	return ret;
}