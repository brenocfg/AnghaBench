#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct io_region {scalar_t__ offset; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {scalar_t__ address; } ;

/* Variables and functions */
 struct io_region const* ARRAY_END (struct io_region*) ; 
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 int EBUSY ; 
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  floppy_release_allocated_regions (int,struct io_region const*) ; 
 struct io_region* io_regions ; 
 int /*<<< orphan*/  request_region (scalar_t__,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int floppy_request_regions(int fdc)
{
	const struct io_region *p;

	for (p = io_regions; p < ARRAY_END(io_regions); p++) {
		if (!request_region(FDCS->address + p->offset,
				    p->size, "floppy")) {
			DPRINT("Floppy io-port 0x%04lx in use\n",
			       FDCS->address + p->offset);
			floppy_release_allocated_regions(fdc, p);
			return -EBUSY;
		}
	}
	return 0;
}