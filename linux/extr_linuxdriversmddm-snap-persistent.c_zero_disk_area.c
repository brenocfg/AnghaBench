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
struct pstore {int /*<<< orphan*/  zero_area; } ;
typedef  int /*<<< orphan*/  chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  area_location (struct pstore*,int /*<<< orphan*/ ) ; 
 int chunk_io (struct pstore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zero_disk_area(struct pstore *ps, chunk_t area)
{
	return chunk_io(ps, ps->zero_area, area_location(ps, area),
			REQ_OP_WRITE, 0, 0);
}