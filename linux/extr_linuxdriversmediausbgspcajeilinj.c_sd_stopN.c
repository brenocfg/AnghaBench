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
typedef  int u8 ;
struct gspca_dev {TYPE_1__** urb; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int* transfer_buffer; int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int /*<<< orphan*/  JEILINJ_DATA_TIMEOUT ; 
 int JEILINJ_MAX_TRANSFER ; 
 int /*<<< orphan*/  jlj_write2 (struct gspca_dev*,int*) ; 
 int /*<<< orphan*/  usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	int i;
	u8 *buf;
	static u8 stop_commands[][2] = {
		{0x71, 0x00},
		{0x70, 0x09},
		{0x71, 0x80},
		{0x70, 0x05}
	};

	for (;;) {
		/* get the image remaining blocks */
		usb_bulk_msg(gspca_dev->dev,
				gspca_dev->urb[0]->pipe,
				gspca_dev->urb[0]->transfer_buffer,
				JEILINJ_MAX_TRANSFER, NULL,
				JEILINJ_DATA_TIMEOUT);

		/* search for 0xff 0xd9  (EOF for JPEG) */
		i = 0;
		buf = gspca_dev->urb[0]->transfer_buffer;
		while ((i < (JEILINJ_MAX_TRANSFER - 1)) &&
			((buf[i] != 0xff) || (buf[i+1] != 0xd9)))
			i++;

		if (i != (JEILINJ_MAX_TRANSFER - 1))
			/* last remaining block found */
			break;
		}

	for (i = 0; i < ARRAY_SIZE(stop_commands); i++)
		jlj_write2(gspca_dev, stop_commands[i]);
}