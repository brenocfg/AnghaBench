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
typedef  int u8 ;
typedef  unsigned int u32 ;
struct TYPE_3__ {int rx2; } ;
struct mceusb_dev {int* buf_in; int txports_cabled; int num_txports; int num_rxports; int learning_active; unsigned int pulse_tunit; unsigned int pulse_count; int emver; int tx_mask; int rxports_active; int need_reset; int /*<<< orphan*/  dev; TYPE_2__* rc; TYPE_1__ flags; int /*<<< orphan*/  carrier_report_enabled; } ;
struct ir_raw_event {int carrier_report; unsigned int carrier; } ;
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
#define  MCE_RSP_CMD_ILLEGAL 136 
#define  MCE_RSP_EQEMVER 135 
#define  MCE_RSP_EQIRNUMPORTS 134 
#define  MCE_RSP_EQIRRXCFCNT 133 
#define  MCE_RSP_EQIRRXPORTEN 132 
#define  MCE_RSP_EQIRTIMEOUT 131 
#define  MCE_RSP_EQIRTXPORTS 130 
#define  MCE_RSP_GETPORTSTATUS 129 
#define  MCE_RSP_TX_TIMEOUT 128 
 int MCE_TIME_UNIT ; 
 int /*<<< orphan*/  US_TO_NS (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  ir_raw_event_store (TYPE_2__*,struct ir_raw_event*) ; 

__attribute__((used)) static void mceusb_handle_command(struct mceusb_dev *ir, int index)
{
	struct ir_raw_event rawir = {};
	u8 hi = ir->buf_in[index + 1] & 0xff;
	u8 lo = ir->buf_in[index + 2] & 0xff;
	u32 carrier_cycles;
	u32 cycles_fix;

	switch (ir->buf_in[index]) {
	/* the one and only 5-byte return value command */
	case MCE_RSP_GETPORTSTATUS:
		if ((ir->buf_in[index + 4] & 0xff) == 0x00)
			ir->txports_cabled |= 1 << hi;
		break;

	/* 2-byte return value commands */
	case MCE_RSP_EQIRTIMEOUT:
		ir->rc->timeout = US_TO_NS((hi << 8 | lo) * MCE_TIME_UNIT);
		break;
	case MCE_RSP_EQIRNUMPORTS:
		ir->num_txports = hi;
		ir->num_rxports = lo;
		break;
	case MCE_RSP_EQIRRXCFCNT:
		/*
		 * The carrier cycle counter can overflow and wrap around
		 * without notice from the device. So frequency measurement
		 * will be inaccurate with long duration IR.
		 *
		 * The long-range (non learning) receiver always reports
		 * zero count so we always ignore its report.
		 */
		if (ir->carrier_report_enabled && ir->learning_active &&
		    ir->pulse_tunit > 0) {
			carrier_cycles = (hi << 8 | lo);
			/*
			 * Adjust carrier cycle count by adding
			 * 1 missed count per pulse "on"
			 */
			cycles_fix = ir->flags.rx2 == 2 ? ir->pulse_count : 0;
			rawir.carrier_report = 1;
			rawir.carrier = (1000000u / MCE_TIME_UNIT) *
					(carrier_cycles + cycles_fix) /
					ir->pulse_tunit;
			dev_dbg(ir->dev, "RX carrier frequency %u Hz (pulse count = %u, cycles = %u, duration = %u, rx2 = %u)",
				rawir.carrier, ir->pulse_count, carrier_cycles,
				ir->pulse_tunit, ir->flags.rx2);
			ir_raw_event_store(ir->rc, &rawir);
		}
		break;

	/* 1-byte return value commands */
	case MCE_RSP_EQEMVER:
		ir->emver = hi;
		break;
	case MCE_RSP_EQIRTXPORTS:
		ir->tx_mask = hi;
		break;
	case MCE_RSP_EQIRRXPORTEN:
		ir->learning_active = ((hi & 0x02) == 0x02);
		if (ir->rxports_active != hi) {
			dev_info(ir->dev, "%s-range (0x%x) receiver active",
				 ir->learning_active ? "short" : "long", hi);
			ir->rxports_active = hi;
		}
		break;
	case MCE_RSP_CMD_ILLEGAL:
	case MCE_RSP_TX_TIMEOUT:
		ir->need_reset = true;
		break;
	default:
		break;
	}
}