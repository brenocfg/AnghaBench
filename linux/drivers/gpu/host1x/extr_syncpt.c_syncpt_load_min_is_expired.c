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
struct host1x_syncpt {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  host1x_hw_syncpt_load (int /*<<< orphan*/ ,struct host1x_syncpt*) ; 
 int host1x_syncpt_is_expired (struct host1x_syncpt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool syncpt_load_min_is_expired(struct host1x_syncpt *sp, u32 thresh)
{
	host1x_hw_syncpt_load(sp->host, sp);

	return host1x_syncpt_is_expired(sp, thresh);
}