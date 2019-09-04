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
struct pgpath {int is_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pgpath* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pgpath *alloc_pgpath(void)
{
	struct pgpath *pgpath = kzalloc(sizeof(*pgpath), GFP_KERNEL);

	if (!pgpath)
		return NULL;

	pgpath->is_active = true;

	return pgpath;
}