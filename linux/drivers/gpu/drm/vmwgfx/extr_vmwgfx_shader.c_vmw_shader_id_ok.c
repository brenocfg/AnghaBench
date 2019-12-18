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
typedef  scalar_t__ SVGA3dShaderType ;

/* Variables and functions */

__attribute__((used)) static bool vmw_shader_id_ok(u32 user_key, SVGA3dShaderType shader_type)
{
	return user_key <= ((1 << 20) - 1) && (unsigned) shader_type < 16;
}