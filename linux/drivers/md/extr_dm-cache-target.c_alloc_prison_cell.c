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
struct dm_bio_prison_cell_v2 {int dummy; } ;
struct cache {int /*<<< orphan*/  prison; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct dm_bio_prison_cell_v2* dm_bio_prison_alloc_cell_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_bio_prison_cell_v2 *alloc_prison_cell(struct cache *cache)
{
	return dm_bio_prison_alloc_cell_v2(cache->prison, GFP_NOIO);
}