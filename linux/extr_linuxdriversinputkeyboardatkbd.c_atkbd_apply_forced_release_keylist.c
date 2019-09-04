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
struct atkbd {int set; int /*<<< orphan*/  force_release_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (unsigned int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atkbd_apply_forced_release_keylist(struct atkbd* atkbd,
						const void *data)
{
	const unsigned int *keys = data;
	unsigned int i;

	if (atkbd->set == 2)
		for (i = 0; keys[i] != -1U; i++)
			__set_bit(keys[i], atkbd->force_release_mask);
}