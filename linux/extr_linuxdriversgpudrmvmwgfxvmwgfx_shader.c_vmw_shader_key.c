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
typedef  int SVGA3dShaderType ;

/* Variables and functions */

__attribute__((used)) static u32 vmw_shader_key(u32 user_key, SVGA3dShaderType shader_type)
{
	return user_key | (shader_type << 20);
}