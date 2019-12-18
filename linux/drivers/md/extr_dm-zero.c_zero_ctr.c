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
struct dm_target {char* error; int num_discard_bios; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int zero_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	if (argc != 0) {
		ti->error = "No arguments required";
		return -EINVAL;
	}

	/*
	 * Silently drop discards, avoiding -EOPNOTSUPP.
	 */
	ti->num_discard_bios = 1;

	return 0;
}