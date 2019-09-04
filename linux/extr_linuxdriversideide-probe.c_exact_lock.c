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
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_disk_and_module (struct gendisk*) ; 

__attribute__((used)) static int exact_lock(dev_t dev, void *data)
{
	struct gendisk *p = data;

	if (!get_disk_and_module(p))
		return -1;
	return 0;
}