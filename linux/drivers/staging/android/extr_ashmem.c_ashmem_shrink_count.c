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
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;

/* Variables and functions */
 unsigned long lru_count ; 

__attribute__((used)) static unsigned long
ashmem_shrink_count(struct shrinker *shrink, struct shrink_control *sc)
{
	/*
	 * note that lru_count is count of pages on the lru, not a count of
	 * objects on the list. This means the scan function needs to return the
	 * number of pages freed, not the number of objects scanned.
	 */
	return lru_count;
}