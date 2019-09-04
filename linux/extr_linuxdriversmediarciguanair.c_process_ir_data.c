#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iguanair {int* buf_in; int version; int bufsize; int cycle_overhead; int tx_overflow; int /*<<< orphan*/  rc; int /*<<< orphan*/  dev; int /*<<< orphan*/  completion; } ;
struct TYPE_5__ {int pulse; int duration; } ;

/* Variables and functions */
#define  CMD_GET_BUFSIZE 135 
#define  CMD_GET_FEATURES 134 
#define  CMD_GET_VERSION 133 
#define  CMD_RECEIVER_OFF 132 
#define  CMD_RECEIVER_ON 131 
#define  CMD_RX_OVERFLOW 130 
#define  CMD_SEND 129 
#define  CMD_TX_OVERFLOW 128 
 int /*<<< orphan*/  DEFINE_IR_RAW_EVENT (TYPE_1__) ; 
 int RX_RESOLUTION ; 
 int US_TO_NS (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_ir_raw_event (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ ir_raw_event_store_with_filter (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ rawir ; 

__attribute__((used)) static void process_ir_data(struct iguanair *ir, unsigned len)
{
	if (len >= 4 && ir->buf_in[0] == 0 && ir->buf_in[1] == 0) {
		switch (ir->buf_in[3]) {
		case CMD_GET_VERSION:
			if (len == 6) {
				ir->version = (ir->buf_in[5] << 8) |
							ir->buf_in[4];
				complete(&ir->completion);
			}
			break;
		case CMD_GET_BUFSIZE:
			if (len >= 5) {
				ir->bufsize = ir->buf_in[4];
				complete(&ir->completion);
			}
			break;
		case CMD_GET_FEATURES:
			if (len > 5) {
				ir->cycle_overhead = ir->buf_in[5];
				complete(&ir->completion);
			}
			break;
		case CMD_TX_OVERFLOW:
			ir->tx_overflow = true;
			/* fall through */
		case CMD_RECEIVER_OFF:
		case CMD_RECEIVER_ON:
		case CMD_SEND:
			complete(&ir->completion);
			break;
		case CMD_RX_OVERFLOW:
			dev_warn(ir->dev, "receive overflow\n");
			ir_raw_event_reset(ir->rc);
			break;
		default:
			dev_warn(ir->dev, "control code %02x received\n",
							ir->buf_in[3]);
			break;
		}
	} else if (len >= 7) {
		DEFINE_IR_RAW_EVENT(rawir);
		unsigned i;
		bool event = false;

		init_ir_raw_event(&rawir);

		for (i = 0; i < 7; i++) {
			if (ir->buf_in[i] == 0x80) {
				rawir.pulse = false;
				rawir.duration = US_TO_NS(21845);
			} else {
				rawir.pulse = (ir->buf_in[i] & 0x80) == 0;
				rawir.duration = ((ir->buf_in[i] & 0x7f) + 1) *
								 RX_RESOLUTION;
			}

			if (ir_raw_event_store_with_filter(ir->rc, &rawir))
				event = true;
		}

		if (event)
			ir_raw_event_handle(ir->rc);
	}
}