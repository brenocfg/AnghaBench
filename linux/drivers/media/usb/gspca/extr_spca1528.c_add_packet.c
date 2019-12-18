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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void add_packet(struct gspca_dev *gspca_dev,
			u8 *data,
			int len)
{
	int i;

	i = 0;
	do {
		if (data[i] == 0xff) {
			gspca_frame_add(gspca_dev, INTER_PACKET,
					data, i + 1);
			len -= i;
			data += i;
			*data = 0x00;
			i = 0;
		}
	} while (++i < len);
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}