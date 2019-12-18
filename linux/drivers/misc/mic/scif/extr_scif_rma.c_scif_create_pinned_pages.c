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
struct scif_pinned_pages {int prot; int /*<<< orphan*/  magic; void* pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIFEP_MAGIC ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  scif_free (struct scif_pinned_pages*,int) ; 
 void* scif_zalloc (int) ; 

__attribute__((used)) static struct scif_pinned_pages *
scif_create_pinned_pages(int nr_pages, int prot)
{
	struct scif_pinned_pages *pin;

	might_sleep();
	pin = scif_zalloc(sizeof(*pin));
	if (!pin)
		goto error;

	pin->pages = scif_zalloc(nr_pages * sizeof(*pin->pages));
	if (!pin->pages)
		goto error_free_pinned_pages;

	pin->prot = prot;
	pin->magic = SCIFEP_MAGIC;
	return pin;

error_free_pinned_pages:
	scif_free(pin, sizeof(*pin));
error:
	return NULL;
}