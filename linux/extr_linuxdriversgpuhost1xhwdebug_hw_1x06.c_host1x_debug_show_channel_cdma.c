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
typedef  scalar_t__ u32 ;
struct output {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mapped; } ;
struct host1x_cdma {TYPE_1__ push_buffer; } ;
struct host1x_channel {struct host1x_cdma cdma; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_CHANNEL_CHANNELSTAT ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_CMDP_CLASS ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_CMDP_OFFSET ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMACTRL ; 
 scalar_t__ HOST1X_CHANNEL_DMACTRL_DMASTOP ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAGET ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAPUT ; 
 scalar_t__ HOST1X_CLASS_HOST1X ; 
 scalar_t__ HOST1X_UCLASS_WAIT_SYNCPT ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 scalar_t__ host1x_ch_readl (struct host1x_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_debug_output (struct output*,char*,...) ; 
 int /*<<< orphan*/  show_channel_gathers (struct output*,struct host1x_cdma*) ; 

__attribute__((used)) static void host1x_debug_show_channel_cdma(struct host1x *host,
					   struct host1x_channel *ch,
					   struct output *o)
{
	struct host1x_cdma *cdma = &ch->cdma;
	u32 dmaput, dmaget, dmactrl;
	u32 offset, class;
	u32 ch_stat;

	dmaput = host1x_ch_readl(ch, HOST1X_CHANNEL_DMAPUT);
	dmaget = host1x_ch_readl(ch, HOST1X_CHANNEL_DMAGET);
	dmactrl = host1x_ch_readl(ch, HOST1X_CHANNEL_DMACTRL);
	offset = host1x_ch_readl(ch, HOST1X_CHANNEL_CMDP_OFFSET);
	class = host1x_ch_readl(ch, HOST1X_CHANNEL_CMDP_CLASS);
	ch_stat = host1x_ch_readl(ch, HOST1X_CHANNEL_CHANNELSTAT);

	host1x_debug_output(o, "%u-%s: ", ch->id, dev_name(ch->dev));

	if (dmactrl & HOST1X_CHANNEL_DMACTRL_DMASTOP ||
	    !ch->cdma.push_buffer.mapped) {
		host1x_debug_output(o, "inactive\n\n");
		return;
	}

	if (class == HOST1X_CLASS_HOST1X && offset == HOST1X_UCLASS_WAIT_SYNCPT)
		host1x_debug_output(o, "waiting on syncpt\n");
	else
		host1x_debug_output(o, "active class %02x, offset %04x\n",
				    class, offset);

	host1x_debug_output(o, "DMAPUT %08x, DMAGET %08x, DMACTL %08x\n",
			    dmaput, dmaget, dmactrl);
	host1x_debug_output(o, "CHANNELSTAT %02x\n", ch_stat);

	show_channel_gathers(o, cdma);
	host1x_debug_output(o, "\n");
}