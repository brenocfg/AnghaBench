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
struct seq_file {int dummy; } ;
struct mddev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mddev_put (struct mddev*) ; 

__attribute__((used)) static void md_seq_stop(struct seq_file *seq, void *v)
{
	struct mddev *mddev = v;

	if (mddev && v != (void*)1 && v != (void*)2)
		mddev_put(mddev);
}