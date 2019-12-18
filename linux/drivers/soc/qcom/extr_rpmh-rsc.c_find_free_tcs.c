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
struct tcs_group {int num_tcs; int offset; int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ tcs_is_free (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_free_tcs(struct tcs_group *tcs)
{
	int i;

	for (i = 0; i < tcs->num_tcs; i++) {
		if (tcs_is_free(tcs->drv, tcs->offset + i))
			return tcs->offset + i;
	}

	return -EBUSY;
}