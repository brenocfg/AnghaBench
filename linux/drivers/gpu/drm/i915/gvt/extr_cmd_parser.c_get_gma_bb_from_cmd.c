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
struct parser_exec_state {struct intel_vgpu* vgpu; } ;
struct intel_vgpu {TYPE_2__* gvt; } ;
struct TYPE_3__ {int gmadr_bytes_in_cmd; } ;
struct TYPE_4__ {TYPE_1__ device_info; } ;

/* Variables and functions */
 unsigned long BATCH_BUFFER_ADDR_HIGH_MASK ; 
 unsigned long BATCH_BUFFER_ADDR_MASK ; 
 unsigned long INTEL_GVT_INVALID_ADDR ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long cmd_val (struct parser_exec_state*,int) ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,int) ; 

__attribute__((used)) static unsigned long get_gma_bb_from_cmd(struct parser_exec_state *s, int index)
{
	unsigned long addr;
	unsigned long gma_high, gma_low;
	struct intel_vgpu *vgpu = s->vgpu;
	int gmadr_bytes = vgpu->gvt->device_info.gmadr_bytes_in_cmd;

	if (WARN_ON(gmadr_bytes != 4 && gmadr_bytes != 8)) {
		gvt_vgpu_err("invalid gma bytes %d\n", gmadr_bytes);
		return INTEL_GVT_INVALID_ADDR;
	}

	gma_low = cmd_val(s, index) & BATCH_BUFFER_ADDR_MASK;
	if (gmadr_bytes == 4) {
		addr = gma_low;
	} else {
		gma_high = cmd_val(s, index + 1) & BATCH_BUFFER_ADDR_HIGH_MASK;
		addr = (((unsigned long)gma_high) << 32) | gma_low;
	}
	return addr;
}