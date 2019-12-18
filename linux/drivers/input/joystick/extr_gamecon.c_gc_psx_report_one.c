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
struct input_dev {int dummy; } ;
struct gc_pad {int /*<<< orphan*/  type; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_SELECT ; 
 int /*<<< orphan*/  BTN_START ; 
 int /*<<< orphan*/  BTN_THUMBL ; 
 int /*<<< orphan*/  BTN_THUMBR ; 
 int /*<<< orphan*/  GC_DDR ; 
#define  GC_PSX_ANALOG 131 
#define  GC_PSX_NEGCON 130 
#define  GC_PSX_NORMAL 129 
#define  GC_PSX_RUMBLE 128 
 int /*<<< orphan*/ * gc_psx_abs ; 
 int /*<<< orphan*/ * gc_psx_btn ; 
 int /*<<< orphan*/ * gc_psx_ddr_btn ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void gc_psx_report_one(struct gc_pad *pad, unsigned char psx_type,
			      unsigned char *data)
{
	struct input_dev *dev = pad->dev;
	int i;

	switch (psx_type) {

	case GC_PSX_RUMBLE:

		input_report_key(dev, BTN_THUMBL, ~data[0] & 0x04);
		input_report_key(dev, BTN_THUMBR, ~data[0] & 0x02);
		/* fall through */

	case GC_PSX_NEGCON:
	case GC_PSX_ANALOG:

		if (pad->type == GC_DDR) {
			for (i = 0; i < 4; i++)
				input_report_key(dev, gc_psx_ddr_btn[i],
						 ~data[0] & (0x10 << i));
		} else {
			for (i = 0; i < 4; i++)
				input_report_abs(dev, gc_psx_abs[i + 2],
						 data[i + 2]);

			input_report_abs(dev, ABS_X,
				!!(data[0] & 0x80) * 128 + !(data[0] & 0x20) * 127);
			input_report_abs(dev, ABS_Y,
				!!(data[0] & 0x10) * 128 + !(data[0] & 0x40) * 127);
		}

		for (i = 0; i < 8; i++)
			input_report_key(dev, gc_psx_btn[i], ~data[1] & (1 << i));

		input_report_key(dev, BTN_START,  ~data[0] & 0x08);
		input_report_key(dev, BTN_SELECT, ~data[0] & 0x01);

		input_sync(dev);

		break;

	case GC_PSX_NORMAL:

		if (pad->type == GC_DDR) {
			for (i = 0; i < 4; i++)
				input_report_key(dev, gc_psx_ddr_btn[i],
						 ~data[0] & (0x10 << i));
		} else {
			input_report_abs(dev, ABS_X,
				!!(data[0] & 0x80) * 128 + !(data[0] & 0x20) * 127);
			input_report_abs(dev, ABS_Y,
				!!(data[0] & 0x10) * 128 + !(data[0] & 0x40) * 127);

			/*
			 * For some reason if the extra axes are left unset
			 * they drift.
			 * for (i = 0; i < 4; i++)
				input_report_abs(dev, gc_psx_abs[i + 2], 128);
			 * This needs to be debugged properly,
			 * maybe fuzz processing needs to be done
			 * in input_sync()
			 *				 --vojtech
			 */
		}

		for (i = 0; i < 8; i++)
			input_report_key(dev, gc_psx_btn[i], ~data[1] & (1 << i));

		input_report_key(dev, BTN_START,  ~data[0] & 0x08);
		input_report_key(dev, BTN_SELECT, ~data[0] & 0x01);

		input_sync(dev);

		break;

	default: /* not a pad, ignore */
		break;
	}
}