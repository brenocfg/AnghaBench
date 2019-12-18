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
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_THRESH_INT_ENABLE_CPU0 (unsigned int) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _host1x_intr_enable_syncpt_intr(struct host1x *host,
					    unsigned int id)
{
	host1x_sync_writel(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_INT_ENABLE_CPU0(id / 32));
}