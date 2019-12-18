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
 int /*<<< orphan*/  PTR_OFFSET (struct bkey const*,unsigned int) ; 
 size_t sector_to_bucket (struct cache_set*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t PTR_BUCKET_NR(struct cache_set *c,
				   const struct bkey *k,
				   unsigned int ptr)
{
	return sector_to_bucket(c, PTR_OFFSET(k, ptr));
}