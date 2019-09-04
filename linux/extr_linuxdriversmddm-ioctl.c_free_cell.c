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
struct hash_cell {struct hash_cell* uuid; struct hash_cell* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hash_cell*) ; 

__attribute__((used)) static void free_cell(struct hash_cell *hc)
{
	if (hc) {
		kfree(hc->name);
		kfree(hc->uuid);
		kfree(hc);
	}
}