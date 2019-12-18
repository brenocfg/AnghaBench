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
typedef  int u8 ;
struct picolcd_data {int status; int /*<<< orphan*/  rc_dev; int /*<<< orphan*/  lock; } ;
struct ir_raw_event {int pulse; int duration; } ;
struct hid_report {int dummy; } ;

/* Variables and functions */
 int PICOLCD_CIR_SHUN ; 
 int US_TO_NS (int) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int picolcd_raw_cir(struct picolcd_data *data,
		struct hid_report *report, u8 *raw_data, int size)
{
	unsigned long flags;
	int i, w, sz;
	struct ir_raw_event rawir = {};

	/* ignore if rc_dev is NULL or status is shunned */
	spin_lock_irqsave(&data->lock, flags);
	if (!data->rc_dev || (data->status & PICOLCD_CIR_SHUN)) {
		spin_unlock_irqrestore(&data->lock, flags);
		return 1;
	}
	spin_unlock_irqrestore(&data->lock, flags);

	/* PicoLCD USB packets contain 16-bit intervals in network order,
	 * with value negated for pulse. Intervals are in microseconds.
	 *
	 * Note: some userspace LIRC code for PicoLCD says negated values
	 * for space - is it a matter of IR chip? (pulse for my TSOP2236)
	 *
	 * In addition, the first interval seems to be around 15000 + base
	 * interval for non-first report of IR data - thus the quirk below
	 * to get RC_CODE to understand Sony and JVC remotes I have at hand
	 */
	sz = size > 0 ? min((int)raw_data[0], size-1) : 0;
	for (i = 0; i+1 < sz; i += 2) {
		w = (raw_data[i] << 8) | (raw_data[i+1]);
		rawir.pulse = !!(w & 0x8000);
		rawir.duration = US_TO_NS(rawir.pulse ? (65536 - w) : w);
		/* Quirk!! - see above */
		if (i == 0 && rawir.duration > 15000000)
			rawir.duration -= 15000000;
		ir_raw_event_store(data->rc_dev, &rawir);
	}
	ir_raw_event_handle(data->rc_dev);

	return 1;
}