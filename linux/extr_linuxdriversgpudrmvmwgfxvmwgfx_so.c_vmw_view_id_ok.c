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
typedef  scalar_t__ u32 ;
typedef  enum vmw_view_type { ____Placeholder_vmw_view_type } vmw_view_type ;

/* Variables and functions */
 scalar_t__ SVGA_COTABLE_MAX_IDS ; 
 int vmw_view_max ; 

__attribute__((used)) static bool vmw_view_id_ok(u32 user_key, enum vmw_view_type view_type)
{
	return (user_key < SVGA_COTABLE_MAX_IDS &&
		view_type < vmw_view_max);
}