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
typedef  scalar_t__ uint32_t ;
struct pstore {scalar_t__ exceptions_per_area; } ;
struct disk_exception {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static struct disk_exception *get_exception(struct pstore *ps, void *ps_area,
					    uint32_t index)
{
	BUG_ON(index >= ps->exceptions_per_area);

	return ((struct disk_exception *) ps_area) + index;
}