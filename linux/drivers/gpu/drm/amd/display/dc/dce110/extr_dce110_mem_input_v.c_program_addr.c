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
struct dce_mem_input {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  luma_addr; int /*<<< orphan*/  chroma_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct dc_plane_address {int type; TYPE_2__ video_progressive; TYPE_1__ grph; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  PLN_ADDR_TYPE_GRAPHICS 129 
#define  PLN_ADDR_TYPE_VIDEO_PROGRESSIVE 128 
 int /*<<< orphan*/  program_pri_addr_c (struct dce_mem_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_pri_addr_l (struct dce_mem_input*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_addr(
	struct dce_mem_input *mem_input110,
	const struct dc_plane_address *addr)
{
	switch (addr->type) {
	case PLN_ADDR_TYPE_GRAPHICS:
		program_pri_addr_l(
			mem_input110,
			addr->grph.addr);
		break;
	case PLN_ADDR_TYPE_VIDEO_PROGRESSIVE:
		program_pri_addr_c(
			mem_input110,
			addr->video_progressive.chroma_addr);
		program_pri_addr_l(
			mem_input110,
			addr->video_progressive.luma_addr);
		break;
	default:
		/* not supported */
		BREAK_TO_DEBUGGER();
	}
}