#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char const u8 ;
typedef  char const u64 ;
typedef  int u32 ;
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  ts ;
struct TYPE_3__ {char const* b; } ;
struct TYPE_4__ {scalar_t__ do_len; TYPE_1__ uuid; } ;
struct sys_t_output {TYPE_2__ node; } ;
struct stm_output {unsigned int channel; unsigned int master; struct sys_t_output* pdrv_private; } ;
struct stm_data {scalar_t__ (* packet ) (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const*) ;} ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int DATA_HEADER ; 
 scalar_t__ EINVAL ; 
 int MIPI_SYST_OPT_LEN ; 
 int MIPI_SYST_OPT_TS ; 
 int /*<<< orphan*/  STP_PACKET_DATA ; 
 int /*<<< orphan*/  STP_PACKET_FLAG ; 
 int /*<<< orphan*/  STP_PACKET_TIMESTAMPED ; 
 size_t UUID_SIZE ; 
 char ktime_get_real_ns () ; 
 scalar_t__ stm_data_write (struct stm_data*,unsigned int,unsigned int,int,char const*,size_t) ; 
 scalar_t__ stub1 (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const*) ; 
 scalar_t__ stub2 (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const*) ; 
 scalar_t__ stub3 (struct stm_data*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char const*) ; 
 scalar_t__ sys_t_clock_sync (struct stm_data*,unsigned int,unsigned int) ; 
 scalar_t__ sys_t_need_clock_sync (struct sys_t_output*) ; 
 scalar_t__ sys_t_need_ts (struct sys_t_output*) ; 

__attribute__((used)) static ssize_t sys_t_write(struct stm_data *data, struct stm_output *output,
			   unsigned int chan, const char *buf, size_t count)
{
	struct sys_t_output *op = output->pdrv_private;
	unsigned int c = output->channel + chan;
	unsigned int m = output->master;
	const unsigned char nil = 0;
	u32 header = DATA_HEADER;
	ssize_t sz;

	/* We require an existing policy node to proceed */
	if (!op)
		return -EINVAL;

	if (sys_t_need_clock_sync(op)) {
		sz = sys_t_clock_sync(data, m, c);
		if (sz <= 0)
			return sz;
	}

	if (op->node.do_len)
		header |= MIPI_SYST_OPT_LEN;
	if (sys_t_need_ts(op))
		header |= MIPI_SYST_OPT_TS;

	/*
	 * STP framing rules for SyS-T frames:
	 *   * the first packet of the SyS-T frame is timestamped;
	 *   * the last packet is a FLAG.
	 */
	/* Message layout: HEADER / GUID / [LENGTH /][TIMESTAMP /] DATA */
	/* HEADER */
	sz = data->packet(data, m, c, STP_PACKET_DATA, STP_PACKET_TIMESTAMPED,
			  4, (u8 *)&header);
	if (sz <= 0)
		return sz;

	/* GUID */
	sz = stm_data_write(data, m, c, false, op->node.uuid.b, UUID_SIZE);
	if (sz <= 0)
		return sz;

	/* [LENGTH] */
	if (op->node.do_len) {
		u16 length = count;

		sz = data->packet(data, m, c, STP_PACKET_DATA, 0, 2,
				  (u8 *)&length);
		if (sz <= 0)
			return sz;
	}

	/* [TIMESTAMP] */
	if (header & MIPI_SYST_OPT_TS) {
		u64 ts = ktime_get_real_ns();

		sz = stm_data_write(data, m, c, false, &ts, sizeof(ts));
		if (sz <= 0)
			return sz;
	}

	/* DATA */
	sz = stm_data_write(data, m, c, false, buf, count);
	if (sz > 0)
		data->packet(data, m, c, STP_PACKET_FLAG, 0, 0, &nil);

	return sz;
}