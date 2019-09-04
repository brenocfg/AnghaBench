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
typedef  scalar_t__ u32 ;
struct output {int dummy; } ;
struct host1x_channel {int /*<<< orphan*/  id; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST1X_CHANNEL_FIFOSTAT ; 
 scalar_t__ HOST1X_CHANNEL_FIFOSTAT_CFEMPTY_V (scalar_t__) ; 
 int /*<<< orphan*/  HOST1X_SYNC_CFPEEK_CTRL ; 
 int HOST1X_SYNC_CFPEEK_CTRL_ADDR_F (scalar_t__) ; 
 int HOST1X_SYNC_CFPEEK_CTRL_CHANNR_F (int /*<<< orphan*/ ) ; 
 int HOST1X_SYNC_CFPEEK_CTRL_ENA_F (int) ; 
 int /*<<< orphan*/  HOST1X_SYNC_CFPEEK_PTRS ; 
 scalar_t__ HOST1X_SYNC_CFPEEK_PTRS_CF_RD_PTR_V (scalar_t__) ; 
 scalar_t__ HOST1X_SYNC_CFPEEK_PTRS_CF_WR_PTR_V (scalar_t__) ; 
 int /*<<< orphan*/  HOST1X_SYNC_CFPEEK_READ ; 
 int /*<<< orphan*/  HOST1X_SYNC_CF_SETUP (int /*<<< orphan*/ ) ; 
 scalar_t__ HOST1X_SYNC_CF_SETUP_BASE_V (scalar_t__) ; 
 scalar_t__ HOST1X_SYNC_CF_SETUP_LIMIT_V (scalar_t__) ; 
 scalar_t__ host1x_ch_readl (struct host1x_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_debug_cont (struct output*,char*,...) ; 
 int /*<<< orphan*/  host1x_debug_output (struct output*,char*,...) ; 
 scalar_t__ host1x_sync_readl (struct host1x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_sync_writel (struct host1x*,int,int /*<<< orphan*/ ) ; 
 unsigned int show_channel_command (struct output*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void host1x_debug_show_channel_fifo(struct host1x *host,
					   struct host1x_channel *ch,
					   struct output *o)
{
	u32 val, rd_ptr, wr_ptr, start, end;
	unsigned int data_count = 0;

	host1x_debug_output(o, "%u: fifo:\n", ch->id);

	val = host1x_ch_readl(ch, HOST1X_CHANNEL_FIFOSTAT);
	host1x_debug_output(o, "FIFOSTAT %08x\n", val);
	if (HOST1X_CHANNEL_FIFOSTAT_CFEMPTY_V(val)) {
		host1x_debug_output(o, "[empty]\n");
		return;
	}

	host1x_sync_writel(host, 0x0, HOST1X_SYNC_CFPEEK_CTRL);
	host1x_sync_writel(host, HOST1X_SYNC_CFPEEK_CTRL_ENA_F(1) |
			   HOST1X_SYNC_CFPEEK_CTRL_CHANNR_F(ch->id),
			   HOST1X_SYNC_CFPEEK_CTRL);

	val = host1x_sync_readl(host, HOST1X_SYNC_CFPEEK_PTRS);
	rd_ptr = HOST1X_SYNC_CFPEEK_PTRS_CF_RD_PTR_V(val);
	wr_ptr = HOST1X_SYNC_CFPEEK_PTRS_CF_WR_PTR_V(val);

	val = host1x_sync_readl(host, HOST1X_SYNC_CF_SETUP(ch->id));
	start = HOST1X_SYNC_CF_SETUP_BASE_V(val);
	end = HOST1X_SYNC_CF_SETUP_LIMIT_V(val);

	do {
		host1x_sync_writel(host, 0x0, HOST1X_SYNC_CFPEEK_CTRL);
		host1x_sync_writel(host, HOST1X_SYNC_CFPEEK_CTRL_ENA_F(1) |
				   HOST1X_SYNC_CFPEEK_CTRL_CHANNR_F(ch->id) |
				   HOST1X_SYNC_CFPEEK_CTRL_ADDR_F(rd_ptr),
				   HOST1X_SYNC_CFPEEK_CTRL);
		val = host1x_sync_readl(host, HOST1X_SYNC_CFPEEK_READ);

		if (!data_count) {
			host1x_debug_output(o, "%08x: ", val);
			data_count = show_channel_command(o, val, NULL);
		} else {
			host1x_debug_cont(o, "%08x%s", val,
					  data_count > 1 ? ", " : "])\n");
			data_count--;
		}

		if (rd_ptr == end)
			rd_ptr = start;
		else
			rd_ptr++;
	} while (rd_ptr != wr_ptr);

	if (data_count)
		host1x_debug_cont(o, ", ...])\n");
	host1x_debug_output(o, "\n");

	host1x_sync_writel(host, 0x0, HOST1X_SYNC_CFPEEK_CTRL);
}