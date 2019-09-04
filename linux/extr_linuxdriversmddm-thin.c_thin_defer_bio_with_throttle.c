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
struct thin_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  throttle; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thin_defer_bio (struct thin_c*,struct bio*) ; 
 int /*<<< orphan*/  throttle_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throttle_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thin_defer_bio_with_throttle(struct thin_c *tc, struct bio *bio)
{
	struct pool *pool = tc->pool;

	throttle_lock(&pool->throttle);
	thin_defer_bio(tc, bio);
	throttle_unlock(&pool->throttle);
}