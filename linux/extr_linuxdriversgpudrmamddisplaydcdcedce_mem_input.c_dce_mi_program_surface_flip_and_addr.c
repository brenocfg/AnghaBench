#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_8__ {int /*<<< orphan*/  quad_part; } ;
struct TYPE_6__ {TYPE_3__ right_addr; TYPE_4__ left_addr; } ;
struct TYPE_5__ {TYPE_4__ addr; } ;
struct dc_plane_address {int type; TYPE_2__ grph_stereo; TYPE_1__ grph; } ;
struct mem_input {struct dc_plane_address current_address; struct dc_plane_address request_address; } ;
struct dce_mem_input {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GRPH_FLIP_CONTROL ; 
 int /*<<< orphan*/  GRPH_SURFACE_UPDATE_H_RETRACE_EN ; 
 int /*<<< orphan*/  GRPH_UPDATE ; 
 int /*<<< orphan*/  GRPH_UPDATE_LOCK ; 
#define  PLN_ADDR_TYPE_GRAPHICS 129 
#define  PLN_ADDR_TYPE_GRPH_STEREO 128 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dce_mem_input* TO_DCE_MEM_INPUT (struct mem_input*) ; 
 int /*<<< orphan*/  program_pri_addr (struct dce_mem_input*,TYPE_4__) ; 
 int /*<<< orphan*/  program_sec_addr (struct dce_mem_input*,TYPE_3__) ; 

__attribute__((used)) static bool dce_mi_program_surface_flip_and_addr(
	struct mem_input *mem_input,
	const struct dc_plane_address *address,
	bool flip_immediate)
{
	struct dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mem_input);

	REG_UPDATE(GRPH_UPDATE, GRPH_UPDATE_LOCK, 1);

	REG_UPDATE(
		GRPH_FLIP_CONTROL,
		GRPH_SURFACE_UPDATE_H_RETRACE_EN, flip_immediate ? 1 : 0);

	switch (address->type) {
	case PLN_ADDR_TYPE_GRAPHICS:
		if (address->grph.addr.quad_part == 0)
			break;
		program_pri_addr(dce_mi, address->grph.addr);
		break;
	case PLN_ADDR_TYPE_GRPH_STEREO:
		if (address->grph_stereo.left_addr.quad_part == 0 ||
		    address->grph_stereo.right_addr.quad_part == 0)
			break;
		program_pri_addr(dce_mi, address->grph_stereo.left_addr);
		program_sec_addr(dce_mi, address->grph_stereo.right_addr);
		break;
	default:
		/* not supported */
		BREAK_TO_DEBUGGER();
		break;
	}

	mem_input->request_address = *address;

	if (flip_immediate)
		mem_input->current_address = *address;

	REG_UPDATE(GRPH_UPDATE, GRPH_UPDATE_LOCK, 0);

	return true;
}