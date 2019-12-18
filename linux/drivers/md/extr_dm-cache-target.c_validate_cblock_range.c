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
typedef  scalar_t__ uint64_t ;
struct cblock_range {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; } ;
struct cache {int /*<<< orphan*/  cache_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 scalar_t__ from_cblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_cblock_range(struct cache *cache, struct cblock_range *range)
{
	uint64_t b = from_cblock(range->begin);
	uint64_t e = from_cblock(range->end);
	uint64_t n = from_cblock(cache->cache_size);

	if (b >= n) {
		DMERR("%s: begin cblock out of range: %llu >= %llu",
		      cache_device_name(cache), b, n);
		return -EINVAL;
	}

	if (e > n) {
		DMERR("%s: end cblock out of range: %llu > %llu",
		      cache_device_name(cache), e, n);
		return -EINVAL;
	}

	if (b >= e) {
		DMERR("%s: invalid cblock range: %llu >= %llu",
		      cache_device_name(cache), b, e);
		return -EINVAL;
	}

	return 0;
}