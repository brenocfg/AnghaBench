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
typedef  int /*<<< orphan*/  uint32_t ;
struct vc4_rcl_setup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC4_PACKET_TILE_COORDINATES ; 
 int /*<<< orphan*/  rcl_u8 (struct vc4_rcl_setup*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vc4_tile_coordinates(struct vc4_rcl_setup *setup,
				 uint32_t x, uint32_t y)
{
	rcl_u8(setup, VC4_PACKET_TILE_COORDINATES);
	rcl_u8(setup, x);
	rcl_u8(setup, y);
}