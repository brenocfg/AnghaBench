#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ block_size; scalar_t__ bucket_size; scalar_t__ nr_in_set; } ;
struct cache_set {TYPE_2__ sb; } ;
struct TYPE_3__ {scalar_t__ block_size; scalar_t__ bucket_size; scalar_t__ nr_in_set; } ;
struct cache {TYPE_1__ sb; } ;

/* Variables and functions */

__attribute__((used)) static bool can_attach_cache(struct cache *ca, struct cache_set *c)
{
	return ca->sb.block_size	== c->sb.block_size &&
		ca->sb.bucket_size	== c->sb.bucket_size &&
		ca->sb.nr_in_set	== c->sb.nr_in_set;
}