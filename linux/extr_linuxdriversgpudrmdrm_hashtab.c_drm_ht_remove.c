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
struct drm_open_hash {int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

void drm_ht_remove(struct drm_open_hash *ht)
{
	if (ht->table) {
		kvfree(ht->table);
		ht->table = NULL;
	}
}