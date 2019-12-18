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
struct host1x {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  nb_pts; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS (unsigned int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE (unsigned int) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _host1x_intr_disable_all_syncpt_intrs(struct host1x *host)
{
	unsigned int i;

	for (i = 0; i < DIV_ROUND_UP(host->info->nb_pts, 32); ++i) {
		host1x_sync_writel(host, 0xffffffffu,
			HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE(i));
		host1x_sync_writel(host, 0xffffffffu,
			HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS(i));
	}
}