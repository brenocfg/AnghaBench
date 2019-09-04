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
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_INT_THRESH (unsigned int) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _host1x_intr_set_syncpt_threshold(struct host1x *host,
					      unsigned int id,
					      u32 thresh)
{
	host1x_sync_writel(host, thresh, HOST1X_SYNC_SYNCPT_INT_THRESH(id));
}