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
struct d0_single_user_mode {int /*<<< orphan*/  num_locking_objects; } ;

/* Variables and functions */
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static bool check_sum(const void *data)
{
	const struct d0_single_user_mode *sum = data;
	u32 nlo = be32_to_cpu(sum->num_locking_objects);

	if (nlo == 0) {
		pr_debug("Need at least one locking object.\n");
		return false;
	}

	pr_debug("Number of locking objects: %d\n", nlo);

	return true;
}