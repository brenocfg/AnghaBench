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
typedef  int u8 ;
typedef  int u64 ;
struct ir_raw_event {int pulse; int duration; } ;
struct imon {TYPE_1__* rcdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  ir_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle; } ;

/* Variables and functions */
 int BIT_DURATION ; 
 int BIT_ULL (int) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int fls64 (int) ; 
 int /*<<< orphan*/  ir_raw_event_handle (TYPE_1__*) ; 
 int /*<<< orphan*/  ir_raw_event_set_idle (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (TYPE_1__*,struct ir_raw_event*) ; 

__attribute__((used)) static void imon_ir_data(struct imon *imon)
{
	struct ir_raw_event rawir = {};
	u64 data = be64_to_cpu(imon->ir_buf);
	u8 packet_no = data & 0xff;
	int offset = 40;
	int bit;

	if (packet_no == 0xff)
		return;

	dev_dbg(imon->dev, "data: %*ph", 8, &imon->ir_buf);

	/*
	 * Only the first 5 bytes contain IR data. Right shift so we move
	 * the IR bits to the lower 40 bits.
	 */
	data >>= 24;

	do {
		/*
		 * Find highest set bit which is less or equal to offset
		 *
		 * offset is the bit above (base 0) where we start looking.
		 *
		 * data & (BIT_ULL(offset) - 1) masks off any unwanted bits,
		 * so we have just bits less than offset.
		 *
		 * fls will tell us the highest bit set plus 1 (or 0 if no
		 * bits are set).
		 */
		bit = fls64(data & (BIT_ULL(offset) - 1));
		if (bit < offset) {
			dev_dbg(imon->dev, "pulse: %d bits", offset - bit);
			rawir.pulse = true;
			rawir.duration = (offset - bit) * BIT_DURATION;
			ir_raw_event_store_with_filter(imon->rcdev, &rawir);

			if (bit == 0)
				break;

			offset = bit;
		}

		/*
		 * Find highest clear bit which is less than offset.
		 *
		 * Just invert the data and use same trick as above.
		 */
		bit = fls64(~data & (BIT_ULL(offset) - 1));
		dev_dbg(imon->dev, "space: %d bits", offset - bit);

		rawir.pulse = false;
		rawir.duration = (offset - bit) * BIT_DURATION;
		ir_raw_event_store_with_filter(imon->rcdev, &rawir);

		offset = bit;
	} while (offset > 0);

	if (packet_no == 0x0a && !imon->rcdev->idle) {
		ir_raw_event_set_idle(imon->rcdev, true);
		ir_raw_event_handle(imon->rcdev);
	}
}