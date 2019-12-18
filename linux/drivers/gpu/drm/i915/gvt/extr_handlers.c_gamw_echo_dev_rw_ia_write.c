#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_vgpu {int /*<<< orphan*/  id; TYPE_1__* gvt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int GAMW_ECO_ENABLE_64K_IPS_FIELD ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_core (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int) ; 
 int /*<<< orphan*/  write_vreg (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int gamw_echo_dev_rw_ia_write(struct intel_vgpu *vgpu,
		unsigned int offset, void *p_data, unsigned int bytes)
{
	u32 ips = (*(u32 *)p_data) & GAMW_ECO_ENABLE_64K_IPS_FIELD;

	if (INTEL_GEN(vgpu->gvt->dev_priv) <= 10) {
		if (ips == GAMW_ECO_ENABLE_64K_IPS_FIELD)
			gvt_dbg_core("vgpu%d: ips enabled\n", vgpu->id);
		else if (!ips)
			gvt_dbg_core("vgpu%d: ips disabled\n", vgpu->id);
		else {
			/* All engines must be enabled together for vGPU,
			 * since we don't know which engine the ppgtt will
			 * bind to when shadowing.
			 */
			gvt_vgpu_err("Unsupported IPS setting %x, cannot enable 64K gtt.\n",
				     ips);
			return -EINVAL;
		}
	}

	write_vreg(vgpu, offset, p_data, bytes);
	return 0;
}