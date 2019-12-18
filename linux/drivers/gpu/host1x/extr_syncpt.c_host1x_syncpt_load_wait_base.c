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
typedef  int /*<<< orphan*/  u32 ;
struct host1x_syncpt {int /*<<< orphan*/  base_val; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_hw_syncpt_load_wait_base (int /*<<< orphan*/ ,struct host1x_syncpt*) ; 

u32 host1x_syncpt_load_wait_base(struct host1x_syncpt *sp)
{
	host1x_hw_syncpt_load_wait_base(sp->host, sp);

	return sp->base_val;
}