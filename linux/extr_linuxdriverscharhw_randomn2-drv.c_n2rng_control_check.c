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
struct n2rng {int num_units; } ;

/* Variables and functions */
 int n2rng_control_selftest (struct n2rng*,int) ; 

__attribute__((used)) static int n2rng_control_check(struct n2rng *np)
{
	int i;

	for (i = 0; i < np->num_units; i++) {
		int err = n2rng_control_selftest(np, i);
		if (err)
			return err;
	}
	return 0;
}