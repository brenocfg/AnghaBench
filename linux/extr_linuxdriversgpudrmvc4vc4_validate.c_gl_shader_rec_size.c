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

/* Variables and functions */

__attribute__((used)) static uint32_t
gl_shader_rec_size(uint32_t pointer_bits)
{
	uint32_t attribute_count = pointer_bits & 7;
	bool extended = pointer_bits & 8;

	if (attribute_count == 0)
		attribute_count = 8;

	if (extended)
		return 100 + attribute_count * 4;
	else
		return 36 + attribute_count * 8;
}