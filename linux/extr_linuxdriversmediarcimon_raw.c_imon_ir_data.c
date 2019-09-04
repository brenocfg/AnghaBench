#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct imon {int* ir_buf; int /*<<< orphan*/  rcdev; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int pulse; int duration; } ;

/* Variables and functions */
 int BIT_DURATION ; 
 int /*<<< orphan*/  DEFINE_IR_RAW_EVENT (TYPE_1__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_set_idle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ is_bit_set (int*,int) ; 
 TYPE_1__ rawir ; 

__attribute__((used)) static void imon_ir_data(struct imon *imon)
{
	DEFINE_IR_RAW_EVENT(rawir);
	int offset = 0, size = 5 * 8;
	int bit;

	dev_dbg(imon->dev, "data: %*ph", 8, imon->ir_buf);

	while (offset < size) {
		bit = offset;
		while (!is_bit_set(imon->ir_buf, bit) && bit < size)
			bit++;
		dev_dbg(imon->dev, "pulse: %d bits", bit - offset);
		if (bit > offset) {
			rawir.pulse = true;
			rawir.duration = (bit - offset) * BIT_DURATION;
			ir_raw_event_store_with_filter(imon->rcdev, &rawir);
		}

		if (bit >= size)
			break;

		offset = bit;
		while (is_bit_set(imon->ir_buf, bit) && bit < size)
			bit++;
		dev_dbg(imon->dev, "space: %d bits", bit - offset);

		rawir.pulse = false;
		rawir.duration = (bit - offset) * BIT_DURATION;
		ir_raw_event_store_with_filter(imon->rcdev, &rawir);

		offset = bit;
	}

	if (imon->ir_buf[7] == 0x0a) {
		ir_raw_event_set_idle(imon->rcdev, true);
		ir_raw_event_handle(imon->rcdev);
	}
}