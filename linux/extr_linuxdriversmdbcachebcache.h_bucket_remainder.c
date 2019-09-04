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
struct TYPE_2__ {int bucket_size; } ;
struct cache_set {TYPE_1__ sb; } ;
typedef  int sector_t ;

/* Variables and functions */

__attribute__((used)) static inline sector_t bucket_remainder(struct cache_set *c, sector_t s)
{
	return s & (c->sb.bucket_size - 1);
}