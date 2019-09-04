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
 int /*<<< orphan*/  CM_READ_ONLY ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  abort_transaction (struct cache*) ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 int /*<<< orphan*/  set_cache_mode (struct cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void metadata_operation_failed(struct cache *cache, const char *op, int r)
{
	DMERR_LIMIT("%s: metadata operation '%s' failed: error = %d",
		    cache_device_name(cache), op, r);
	abort_transaction(cache);
	set_cache_mode(cache, CM_READ_ONLY);
}