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

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void free_pasid_states_level1(struct pasid_state **tbl)
{
	int i;

	for (i = 0; i < 512; ++i) {
		if (tbl[i] == NULL)
			continue;

		free_page((unsigned long)tbl[i]);
	}
}