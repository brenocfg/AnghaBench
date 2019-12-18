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
struct host1x_channel {int /*<<< orphan*/  id; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_TEARDOWN ; 
 int /*<<< orphan*/  HOST1X_SYNC_CH_TEARDOWN ; 
 int /*<<< orphan*/  host1x_ch_writel (struct host1x_channel*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdma_hw_teardown(struct host1x *host, struct host1x_channel *ch)
{
#if HOST1X_HW >= 6
	host1x_ch_writel(ch, 0x1, HOST1X_CHANNEL_TEARDOWN);
#else
	host1x_sync_writel(host, BIT(ch->id), HOST1X_SYNC_CH_TEARDOWN);
#endif
}