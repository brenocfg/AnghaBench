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
struct host1x_syncpt {int /*<<< orphan*/  id; struct host1x* host; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_read_min (struct host1x_syncpt*) ; 

__attribute__((used)) static void syncpt_restore(struct host1x_syncpt *sp)
{
	u32 min = host1x_syncpt_read_min(sp);
	struct host1x *host = sp->host;

	host1x_sync_writel(host, min, HOST1X_SYNC_SYNCPT(sp->id));
}