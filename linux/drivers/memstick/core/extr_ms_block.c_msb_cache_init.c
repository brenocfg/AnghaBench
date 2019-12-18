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
struct msb_data {scalar_t__ cache; int /*<<< orphan*/  block_size; int /*<<< orphan*/  cache_flush_timer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msb_cache_discard (struct msb_data*) ; 
 int /*<<< orphan*/  msb_cache_flush_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msb_cache_init(struct msb_data *msb)
{
	timer_setup(&msb->cache_flush_timer, msb_cache_flush_timer, 0);

	if (!msb->cache)
		msb->cache = kzalloc(msb->block_size, GFP_KERNEL);
	if (!msb->cache)
		return -ENOMEM;

	msb_cache_discard(msb);
	return 0;
}