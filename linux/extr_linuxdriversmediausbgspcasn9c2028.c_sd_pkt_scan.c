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
struct gspca_dev {int dummy; } ;
typedef  unsigned char __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned char* sn9c2028_find_sof (struct gspca_dev*,unsigned char*,int) ; 
 unsigned char* sn9c2028_sof_marker ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			__u8 *data,			/* isoc packet */
			int len)			/* iso packet length */
{
	unsigned char *sof;

	sof = sn9c2028_find_sof(gspca_dev, data, len);
	if (sof) {
		int n;

		/* finish decoding current frame */
		n = sof - data;
		if (n > sizeof sn9c2028_sof_marker)
			n -= sizeof sn9c2028_sof_marker;
		else
			n = 0;
		gspca_frame_add(gspca_dev, LAST_PACKET, data, n);
		/* Start next frame. */
		gspca_frame_add(gspca_dev, FIRST_PACKET,
			sn9c2028_sof_marker, sizeof sn9c2028_sof_marker);
		len -= sof - data;
		data = sof;
	}
	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}