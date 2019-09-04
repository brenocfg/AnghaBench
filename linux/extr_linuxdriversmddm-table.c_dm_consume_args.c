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
struct dm_arg_set {unsigned int argc; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

void dm_consume_args(struct dm_arg_set *as, unsigned num_args)
{
	BUG_ON(as->argc < num_args);
	as->argc -= num_args;
	as->argv += num_args;
}