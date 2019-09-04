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
typedef  int uint32_t ;
struct vc4_validated_shader_info {int num_uniform_addr_offsets; int uniforms_size; int* uniform_addr_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* krealloc (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool require_uniform_address_uniform(struct vc4_validated_shader_info *validated_shader)
{
	uint32_t o = validated_shader->num_uniform_addr_offsets;
	uint32_t num_uniforms = validated_shader->uniforms_size / 4;

	validated_shader->uniform_addr_offsets =
		krealloc(validated_shader->uniform_addr_offsets,
			 (o + 1) *
			 sizeof(*validated_shader->uniform_addr_offsets),
			 GFP_KERNEL);
	if (!validated_shader->uniform_addr_offsets)
		return false;

	validated_shader->uniform_addr_offsets[o] = num_uniforms;
	validated_shader->num_uniform_addr_offsets++;

	return true;
}