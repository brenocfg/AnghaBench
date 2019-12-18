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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sample_period; } ;
struct ite_dev {int /*<<< orphan*/  rdev; TYPE_1__ params; } ;
struct ir_raw_event {int pulse; void* duration; } ;

/* Variables and functions */
 void* ITE_BITS_TO_NS (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int find_next_bit_le (unsigned long*,unsigned int,unsigned int) ; 
 unsigned int find_next_zero_bit_le (unsigned long*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 int /*<<< orphan*/  ite_dbg_verbose (char*,int) ; 

__attribute__((used)) static void ite_decode_bytes(struct ite_dev *dev, const u8 * data, int
			     length)
{
	u32 sample_period;
	unsigned long *ldata;
	unsigned int next_one, next_zero, size;
	struct ir_raw_event ev = {};

	if (length == 0)
		return;

	sample_period = dev->params.sample_period;
	ldata = (unsigned long *)data;
	size = length << 3;
	next_one = find_next_bit_le(ldata, size, 0);
	if (next_one > 0) {
		ev.pulse = true;
		ev.duration =
		    ITE_BITS_TO_NS(next_one, sample_period);
		ir_raw_event_store_with_filter(dev->rdev, &ev);
	}

	while (next_one < size) {
		next_zero = find_next_zero_bit_le(ldata, size, next_one + 1);
		ev.pulse = false;
		ev.duration = ITE_BITS_TO_NS(next_zero - next_one, sample_period);
		ir_raw_event_store_with_filter(dev->rdev, &ev);

		if (next_zero < size) {
			next_one =
			    find_next_bit_le(ldata,
						     size,
						     next_zero + 1);
			ev.pulse = true;
			ev.duration =
			    ITE_BITS_TO_NS(next_one - next_zero,
					   sample_period);
			ir_raw_event_store_with_filter
			    (dev->rdev, &ev);
		} else
			next_one = size;
	}

	ir_raw_event_handle(dev->rdev);

	ite_dbg_verbose("decoded %d bytes.", length);
}