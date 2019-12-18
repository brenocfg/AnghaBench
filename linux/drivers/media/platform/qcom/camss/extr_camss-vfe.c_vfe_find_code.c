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

/* Variables and functions */

__attribute__((used)) static u32 vfe_find_code(u32 *code, unsigned int n_code,
			 unsigned int index, u32 req_code)
{
	int i;

	if (!req_code && (index >= n_code))
		return 0;

	for (i = 0; i < n_code; i++)
		if (req_code) {
			if (req_code == code[i])
				return req_code;
		} else {
			if (i == index)
				return code[i];
		}

	return code[0];
}