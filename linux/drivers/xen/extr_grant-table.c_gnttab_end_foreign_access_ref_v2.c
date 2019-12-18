#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t grant_ref_t ;
struct TYPE_6__ {TYPE_2__* v2; } ;
struct TYPE_4__ {scalar_t__ flags; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int GTF_reading ; 
 int GTF_writing ; 
 int /*<<< orphan*/  barrier () ; 
 TYPE_3__ gnttab_shared ; 
 int* grstatus ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static int gnttab_end_foreign_access_ref_v2(grant_ref_t ref, int readonly)
{
	gnttab_shared.v2[ref].hdr.flags = 0;
	mb();	/* Concurrent access by hypervisor. */
	if (grstatus[ref] & (GTF_reading|GTF_writing)) {
		return 0;
	} else {
		/*
		 * The read of grstatus needs to have acquire semantics.
		 *  On x86, reads already have that, and we just need to
		 * protect against compiler reorderings.
		 * On other architectures we may need a full barrier.
		 */
#ifdef CONFIG_X86
		barrier();
#else
		mb();
#endif
	}

	return 1;
}