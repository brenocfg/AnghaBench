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
struct pstore {int /*<<< orphan*/  area; int /*<<< orphan*/  current_area; } ;
typedef  int /*<<< orphan*/  chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  area_location (struct pstore*,int /*<<< orphan*/ ) ; 
 int chunk_io (struct pstore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int area_io(struct pstore *ps, int op, int op_flags)
{
	int r;
	chunk_t chunk;

	chunk = area_location(ps, ps->current_area);

	r = chunk_io(ps, ps->area, chunk, op, op_flags, 0);
	if (r)
		return r;

	return 0;
}