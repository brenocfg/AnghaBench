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
struct nubus_dir {scalar_t__ done; int /*<<< orphan*/  base; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */

int nubus_rewinddir(struct nubus_dir *dir)
{
	dir->ptr = dir->base;
	dir->done = 0;
	return 0;
}