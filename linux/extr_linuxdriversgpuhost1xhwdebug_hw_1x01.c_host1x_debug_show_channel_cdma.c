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
struct output {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mapped; } ;
struct host1x_cdma {TYPE_1__ push_buffer; } ;
struct host1x_channel {struct host1x_cdma cdma; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_CHANNEL_DMACTRL ; 
 scalar_t__ HOST1X_CHANNEL_DMACTRL_DMASTOP_V (int) ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAGET ; 
 int /*<<< orphan*/  HOST1X_CHANNEL_DMAPUT ; 
 int /*<<< orphan*/  HOST1X_CLASS_HOST1X ; 
 int /*<<< orphan*/  HOST1X_SYNC_CBREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST1X_SYNC_CBSTAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST1X_SYNC_CBSTAT_CBCLASS_V (int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_CBSTAT_CBOFFSET_V (int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_SYNCPT_BASE (int) ; 
 int /*<<< orphan*/  HOST1X_UCLASS_WAIT_SYNCPT ; 
 int /*<<< orphan*/  HOST1X_UCLASS_WAIT_SYNCPT_BASE ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int host1x_ch_readl (struct host1x_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_debug_output (struct output*,char*,...) ; 
 int host1x_sync_readl (struct host1x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_channel_gathers (struct output*,struct host1x_cdma*) ; 

__attribute__((used)) static void host1x_debug_show_channel_cdma(struct host1x *host,
					   struct host1x_channel *ch,
					   struct output *o)
{
	struct host1x_cdma *cdma = &ch->cdma;
	u32 dmaput, dmaget, dmactrl;
	u32 cbstat, cbread;
	u32 val, base, baseval;

	dmaput = host1x_ch_readl(ch, HOST1X_CHANNEL_DMAPUT);
	dmaget = host1x_ch_readl(ch, HOST1X_CHANNEL_DMAGET);
	dmactrl = host1x_ch_readl(ch, HOST1X_CHANNEL_DMACTRL);
	cbread = host1x_sync_readl(host, HOST1X_SYNC_CBREAD(ch->id));
	cbstat = host1x_sync_readl(host, HOST1X_SYNC_CBSTAT(ch->id));

	host1x_debug_output(o, "%u-%s: ", ch->id, dev_name(ch->dev));

	if (HOST1X_CHANNEL_DMACTRL_DMASTOP_V(dmactrl) ||
	    !ch->cdma.push_buffer.mapped) {
		host1x_debug_output(o, "inactive\n\n");
		return;
	}

	if (HOST1X_SYNC_CBSTAT_CBCLASS_V(cbstat) == HOST1X_CLASS_HOST1X &&
	    HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat) ==
			HOST1X_UCLASS_WAIT_SYNCPT)
		host1x_debug_output(o, "waiting on syncpt %d val %d\n",
				    cbread >> 24, cbread & 0xffffff);
	else if (HOST1X_SYNC_CBSTAT_CBCLASS_V(cbstat) ==
				HOST1X_CLASS_HOST1X &&
		 HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat) ==
				HOST1X_UCLASS_WAIT_SYNCPT_BASE) {
		base = (cbread >> 16) & 0xff;
		baseval =
			host1x_sync_readl(host, HOST1X_SYNC_SYNCPT_BASE(base));
		val = cbread & 0xffff;
		host1x_debug_output(o, "waiting on syncpt %d val %d (base %d = %d; offset = %d)\n",
				    cbread >> 24, baseval + val, base,
				    baseval, val);
	} else
		host1x_debug_output(o, "active class %02x, offset %04x, val %08x\n",
				    HOST1X_SYNC_CBSTAT_CBCLASS_V(cbstat),
				    HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat),
				    cbread);

	host1x_debug_output(o, "DMAPUT %08x, DMAGET %08x, DMACTL %08x\n",
			    dmaput, dmaget, dmactrl);
	host1x_debug_output(o, "CBREAD %08x, CBSTAT %08x\n", cbread, cbstat);

	show_channel_gathers(o, cdma);
	host1x_debug_output(o, "\n");
}