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
struct host1x_channel {int id; } ;
struct host1x {int /*<<< orphan*/  hv_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_CHANNELCTRL ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_CHANNELCTRL_KERNEL_FILTER_GBUFFER (int) ; 
 int /*<<< orphan*/  HOST1X_HV_CH_KERNEL_FILTER_GBUFFER (int) ; 
 int /*<<< orphan*/  host1x_ch_writel (struct host1x_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hypervisor_readl (struct host1x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hypervisor_writel (struct host1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_gather_filter(struct host1x *host,
				 struct host1x_channel *ch)
{
#if HOST1X_HW >= 6
	u32 val;

	if (!host->hv_regs)
		return;

	val = host1x_hypervisor_readl(
		host, HOST1X_HV_CH_KERNEL_FILTER_GBUFFER(ch->id / 32));
	val |= BIT(ch->id % 32);
	host1x_hypervisor_writel(
		host, val, HOST1X_HV_CH_KERNEL_FILTER_GBUFFER(ch->id / 32));
#elif HOST1X_HW >= 4
	host1x_ch_writel(ch,
			 HOST1X_CHANNEL_CHANNELCTRL_KERNEL_FILTER_GBUFFER(1),
			 HOST1X_CHANNEL_CHANNELCTRL);
#endif
}