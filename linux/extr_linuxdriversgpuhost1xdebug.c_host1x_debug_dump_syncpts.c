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
struct output {int /*<<< orphan*/  fn; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  show_syncpts (struct host1x*,struct output*) ; 
 int /*<<< orphan*/  write_to_printk ; 

void host1x_debug_dump_syncpts(struct host1x *host1x)
{
	struct output o = {
		.fn = write_to_printk
	};

	show_syncpts(host1x, &o);
}