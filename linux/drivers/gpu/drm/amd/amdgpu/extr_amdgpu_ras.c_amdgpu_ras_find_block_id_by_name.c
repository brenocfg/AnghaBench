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
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ras_block_str (int) ; 
 int /*<<< orphan*/  ras_block_string ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_ras_find_block_id_by_name(const char *name, int *block_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ras_block_string); i++) {
		*block_id = i;
		if (strcmp(name, ras_block_str(i)) == 0)
			return 0;
	}
	return -EINVAL;
}