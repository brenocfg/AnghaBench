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
struct cache_set {int dummy; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_CACHES_PER_SET ; 
 scalar_t__ PTR_CACHE (struct cache_set*,struct bkey const*,unsigned int) ; 
 scalar_t__ PTR_DEV (struct bkey const*,unsigned int) ; 

__attribute__((used)) static inline bool ptr_available(struct cache_set *c, const struct bkey *k,
				 unsigned int i)
{
	return (PTR_DEV(k, i) < MAX_CACHES_PER_SET) && PTR_CACHE(c, k, i);
}