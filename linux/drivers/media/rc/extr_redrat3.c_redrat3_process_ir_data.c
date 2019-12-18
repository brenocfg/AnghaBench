#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {unsigned int* sigdata; int /*<<< orphan*/ * lens; int /*<<< orphan*/  sig_size; } ;
struct redrat3_dev {TYPE_2__* rc; TYPE_1__ irdata; scalar_t__ wideband; struct device* dev; } ;
struct ir_raw_event {int carrier_report; int pulse; int timeout; int /*<<< orphan*/  duration; scalar_t__ carrier; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  IR_MAX_DURATION ; 
 int /*<<< orphan*/  US_TO_NS (unsigned int) ; 
 unsigned int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 unsigned int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_raw_event_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  ir_raw_event_store (TYPE_2__*,struct ir_raw_event*) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (TYPE_2__*,struct ir_raw_event*) ; 
 unsigned int redrat3_len_to_us (unsigned int) ; 
 scalar_t__ redrat3_val_to_mod_freq (TYPE_1__*) ; 

__attribute__((used)) static void redrat3_process_ir_data(struct redrat3_dev *rr3)
{
	struct ir_raw_event rawir = {};
	struct device *dev;
	unsigned int i, sig_size, single_len, offset, val;
	u32 mod_freq;

	dev = rr3->dev;

	mod_freq = redrat3_val_to_mod_freq(&rr3->irdata);
	dev_dbg(dev, "Got mod_freq of %u\n", mod_freq);
	if (mod_freq && rr3->wideband) {
		struct ir_raw_event ev = {
			.carrier_report = 1,
			.carrier = mod_freq
		};

		ir_raw_event_store(rr3->rc, &ev);
	}

	/* process each rr3 encoded byte into an int */
	sig_size = be16_to_cpu(rr3->irdata.sig_size);
	for (i = 0; i < sig_size; i++) {
		offset = rr3->irdata.sigdata[i];
		val = get_unaligned_be16(&rr3->irdata.lens[offset]);
		single_len = redrat3_len_to_us(val);

		/* we should always get pulse/space/pulse/space samples */
		if (i % 2)
			rawir.pulse = false;
		else
			rawir.pulse = true;

		rawir.duration = US_TO_NS(single_len);
		/* cap the value to IR_MAX_DURATION */
		rawir.duration = (rawir.duration > IR_MAX_DURATION) ?
				 IR_MAX_DURATION : rawir.duration;

		dev_dbg(dev, "storing %s with duration %d (i: %d)\n",
			rawir.pulse ? "pulse" : "space", rawir.duration, i);
		ir_raw_event_store_with_filter(rr3->rc, &rawir);
	}

	/* add a trailing space */
	rawir.pulse = false;
	rawir.timeout = true;
	rawir.duration = rr3->rc->timeout;
	dev_dbg(dev, "storing trailing timeout with duration %d\n",
							rawir.duration);
	ir_raw_event_store_with_filter(rr3->rc, &rawir);

	dev_dbg(dev, "calling ir_raw_event_handle\n");
	ir_raw_event_handle(rr3->rc);
}