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
struct cache {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ cache_size (struct cache const*,unsigned int*) ; 

__attribute__((used)) static int cache_size_kb(const struct cache *cache, unsigned int *ret)
{
	unsigned int size;

	if (cache_size(cache, &size))
		return -ENODEV;

	*ret = size / 1024;
	return 0;
}