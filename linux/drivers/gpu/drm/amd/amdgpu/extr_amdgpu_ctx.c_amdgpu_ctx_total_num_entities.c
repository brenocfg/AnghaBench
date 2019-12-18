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

/* Variables and functions */
 unsigned int AMDGPU_HW_IP_NUM ; 
 scalar_t__* amdgpu_ctx_num_entities ; 

__attribute__((used)) static int amdgpu_ctx_total_num_entities(void)
{
	unsigned i, num_entities = 0;

	for (i = 0; i < AMDGPU_HW_IP_NUM; ++i)
		num_entities += amdgpu_ctx_num_entities[i];

	return num_entities;
}