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
struct discard_load_info {scalar_t__ discard_end; scalar_t__ discard_begin; struct cache* cache; } ;
struct cache {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void discard_load_info_init(struct cache *cache,
				   struct discard_load_info *li)
{
	li->cache = cache;
	li->discard_begin = li->discard_end = 0;
}