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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ end; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 scalar_t__ CACHE_VALID_JIFFIES ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int fill_dst (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sthyi_cache ; 

__attribute__((used)) static int sthyi_update_cache(u64 *rc)
{
	int r;

	memset(sthyi_cache.info, 0, PAGE_SIZE);
	r = fill_dst(sthyi_cache.info, rc);
	if (r)
		return r;
	sthyi_cache.end = jiffies + CACHE_VALID_JIFFIES;
	return r;
}