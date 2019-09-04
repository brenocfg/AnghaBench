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
struct TYPE_2__ {int mode; } ;
struct cache {TYPE_1__ features; } ;
typedef  enum cache_metadata_mode { ____Placeholder_cache_metadata_mode } cache_metadata_mode ;

/* Variables and functions */

__attribute__((used)) static enum cache_metadata_mode get_cache_mode(struct cache *cache)
{
	return cache->features.mode;
}