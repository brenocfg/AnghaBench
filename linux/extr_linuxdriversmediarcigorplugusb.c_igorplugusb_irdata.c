#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct igorplugusb {unsigned int* buf_in; TYPE_2__* rc; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int timeout; } ;
struct TYPE_6__ {int duration; unsigned int pulse; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IR_RAW_EVENT (TYPE_1__) ; 
 unsigned int HEADERLEN ; 
 int /*<<< orphan*/  SET_INFRABUFFER_EMPTY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  igorplugusb_cmd (struct igorplugusb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__ rawir ; 

__attribute__((used)) static void igorplugusb_irdata(struct igorplugusb *ir, unsigned len)
{
	DEFINE_IR_RAW_EVENT(rawir);
	unsigned i, start, overflow;

	dev_dbg(ir->dev, "irdata: %*ph (len=%u)", len, ir->buf_in, len);

	/*
	 * If more than 36 pulses and spaces follow each other, the igorplugusb
	 * overwrites its buffer from the beginning. The overflow value is the
	 * last offset which was not overwritten. Everything from this offset
	 * onwards occurred before everything until this offset.
	 */
	overflow = ir->buf_in[2];
	i = start = overflow + HEADERLEN;

	if (start >= len) {
		dev_err(ir->dev, "receive overflow invalid: %u", overflow);
	} else {
		if (overflow > 0)
			dev_warn(ir->dev, "receive overflow, at least %u lost",
								overflow);

		do {
			rawir.duration = ir->buf_in[i] * 85333;
			rawir.pulse = i & 1;

			ir_raw_event_store_with_filter(ir->rc, &rawir);

			if (++i == len)
				i = HEADERLEN;
		} while (i != start);

		/* add a trailing space */
		rawir.duration = ir->rc->timeout;
		rawir.pulse = false;
		ir_raw_event_store_with_filter(ir->rc, &rawir);

		ir_raw_event_handle(ir->rc);
	}

	igorplugusb_cmd(ir, SET_INFRABUFFER_EMPTY);
}