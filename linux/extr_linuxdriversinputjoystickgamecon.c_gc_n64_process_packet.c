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
struct input_dev {int dummy; } ;
struct gc {TYPE_1__* pads; } ;
struct TYPE_2__ {scalar_t__ type; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int GC_MAX_DEVICES ; 
 scalar_t__ GC_N64 ; 
 int GC_N64_LENGTH ; 
 int /*<<< orphan*/ * gc_n64_btn ; 
 size_t* gc_n64_bytes ; 
 int /*<<< orphan*/  gc_n64_read_packet (struct gc*,unsigned char*) ; 
 int* gc_status_bit ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gc_n64_process_packet(struct gc *gc)
{
	unsigned char data[GC_N64_LENGTH];
	struct input_dev *dev;
	int i, j, s;
	signed char x, y;

	gc_n64_read_packet(gc, data);

	for (i = 0; i < GC_MAX_DEVICES; i++) {

		if (gc->pads[i].type != GC_N64)
			continue;

		dev = gc->pads[i].dev;
		s = gc_status_bit[i];

		if (s & ~(data[8] | data[9])) {

			x = y = 0;

			for (j = 0; j < 8; j++) {
				if (data[23 - j] & s)
					x |= 1 << j;
				if (data[31 - j] & s)
					y |= 1 << j;
			}

			input_report_abs(dev, ABS_X,  x);
			input_report_abs(dev, ABS_Y, -y);

			input_report_abs(dev, ABS_HAT0X,
					 !(s & data[6]) - !(s & data[7]));
			input_report_abs(dev, ABS_HAT0Y,
					 !(s & data[4]) - !(s & data[5]));

			for (j = 0; j < 10; j++)
				input_report_key(dev, gc_n64_btn[j],
						 s & data[gc_n64_bytes[j]]);

			input_sync(dev);
		}
	}
}