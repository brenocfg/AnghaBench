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
struct vc4_rcl_setup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC4_LOADSTORE_TILE_BUFFER_BUFFER ; 
 int /*<<< orphan*/  VC4_LOADSTORE_TILE_BUFFER_NONE ; 
 int /*<<< orphan*/  VC4_PACKET_STORE_TILE_BUFFER_GENERAL ; 
 int VC4_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VC4_STORE_TILE_BUFFER_DISABLE_COLOR_CLEAR ; 
 int VC4_STORE_TILE_BUFFER_DISABLE_VG_MASK_CLEAR ; 
 int VC4_STORE_TILE_BUFFER_DISABLE_ZS_CLEAR ; 
 int /*<<< orphan*/  rcl_u16 (struct vc4_rcl_setup*,int) ; 
 int /*<<< orphan*/  rcl_u32 (struct vc4_rcl_setup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcl_u8 (struct vc4_rcl_setup*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_store_before_load(struct vc4_rcl_setup *setup)
{
	rcl_u8(setup, VC4_PACKET_STORE_TILE_BUFFER_GENERAL);
	rcl_u16(setup,
		VC4_SET_FIELD(VC4_LOADSTORE_TILE_BUFFER_NONE,
			      VC4_LOADSTORE_TILE_BUFFER_BUFFER) |
		VC4_STORE_TILE_BUFFER_DISABLE_COLOR_CLEAR |
		VC4_STORE_TILE_BUFFER_DISABLE_ZS_CLEAR |
		VC4_STORE_TILE_BUFFER_DISABLE_VG_MASK_CLEAR);
	rcl_u32(setup, 0); /* no address, since we're in None mode */
}