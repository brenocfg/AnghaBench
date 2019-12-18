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
typedef  int u32 ;

/* Variables and functions */
 int MI_WAIT_FOR_PLANE_A_FLIP_PENDING ; 
 int MI_WAIT_FOR_PLANE_B_FLIP_PENDING ; 
 int MI_WAIT_FOR_PLANE_C_FLIP_PENDING ; 
 int MI_WAIT_FOR_SPRITE_A_FLIP_PENDING ; 
 int MI_WAIT_FOR_SPRITE_B_FLIP_PENDING ; 
 int MI_WAIT_FOR_SPRITE_C_FLIP_PENDING ; 

__attribute__((used)) static bool is_wait_for_flip_pending(u32 cmd)
{
	return cmd & (MI_WAIT_FOR_PLANE_A_FLIP_PENDING |
			MI_WAIT_FOR_PLANE_B_FLIP_PENDING |
			MI_WAIT_FOR_PLANE_C_FLIP_PENDING |
			MI_WAIT_FOR_SPRITE_A_FLIP_PENDING |
			MI_WAIT_FOR_SPRITE_B_FLIP_PENDING |
			MI_WAIT_FOR_SPRITE_C_FLIP_PENDING);
}