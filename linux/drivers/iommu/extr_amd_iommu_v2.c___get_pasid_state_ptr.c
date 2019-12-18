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
struct pasid_state {int dummy; } ;
struct device_state {int pasid_levels; struct pasid_state** states; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pasid_state **__get_pasid_state_ptr(struct device_state *dev_state,
						  int pasid, bool alloc)
{
	struct pasid_state **root, **ptr;
	int level, index;

	level = dev_state->pasid_levels;
	root  = dev_state->states;

	while (true) {

		index = (pasid >> (9 * level)) & 0x1ff;
		ptr   = &root[index];

		if (level == 0)
			break;

		if (*ptr == NULL) {
			if (!alloc)
				return NULL;

			*ptr = (void *)get_zeroed_page(GFP_ATOMIC);
			if (*ptr == NULL)
				return NULL;
		}

		root   = (struct pasid_state **)*ptr;
		level -= 1;
	}

	return ptr;
}