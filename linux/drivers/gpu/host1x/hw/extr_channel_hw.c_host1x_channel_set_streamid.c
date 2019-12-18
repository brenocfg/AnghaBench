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
typedef  int u32 ;
struct iommu_fwspec {int* ids; } ;
struct host1x_channel {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_CHANNEL_SMMU_STREAMID ; 
 struct iommu_fwspec* dev_iommu_fwspec_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_ch_writel (struct host1x_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void host1x_channel_set_streamid(struct host1x_channel *channel)
{
#if HOST1X_HW >= 6
	u32 sid = 0x7f;
#ifdef CONFIG_IOMMU_API
	struct iommu_fwspec *spec = dev_iommu_fwspec_get(channel->dev->parent);
	if (spec)
		sid = spec->ids[0] & 0xffff;
#endif

	host1x_ch_writel(channel, sid, HOST1X_CHANNEL_SMMU_STREAMID);
#endif
}