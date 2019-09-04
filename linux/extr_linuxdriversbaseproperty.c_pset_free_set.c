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
struct property_set {int /*<<< orphan*/  properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct property_set*) ; 
 int /*<<< orphan*/  property_entries_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pset_free_set(struct property_set *pset)
{
	if (!pset)
		return;

	property_entries_free(pset->properties);
	kfree(pset);
}