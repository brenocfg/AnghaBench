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
struct mes_resume_gang_input {int dummy; } ;
struct amdgpu_mes {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mes_v10_1_resume_gang(struct amdgpu_mes *mes,
				 struct mes_resume_gang_input *input)
{
	return 0;
}