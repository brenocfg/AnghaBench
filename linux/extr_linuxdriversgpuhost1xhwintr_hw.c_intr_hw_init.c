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
typedef  int u32 ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_SYNC_CTXSW_TIMEOUT_CFG ; 
 int /*<<< orphan*/  HOST1X_SYNC_IP_BUSY_TIMEOUT ; 
 int /*<<< orphan*/  HOST1X_SYNC_USEC_CLK ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intr_hw_init(struct host1x *host, u32 cpm)
{
#if HOST1X_HW < 6
	/* disable the ip_busy_timeout. this prevents write drops */
	host1x_sync_writel(host, 0, HOST1X_SYNC_IP_BUSY_TIMEOUT);

	/*
	 * increase the auto-ack timout to the maximum value. 2d will hang
	 * otherwise on Tegra2.
	 */
	host1x_sync_writel(host, 0xff, HOST1X_SYNC_CTXSW_TIMEOUT_CFG);

	/* update host clocks per usec */
	host1x_sync_writel(host, cpm, HOST1X_SYNC_USEC_CLK);
#endif
}