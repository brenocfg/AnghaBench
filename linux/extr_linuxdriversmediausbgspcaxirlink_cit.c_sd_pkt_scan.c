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
typedef  unsigned char u8 ;
struct sd {int sof_len; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 unsigned char* cit_find_sof (struct gspca_dev*,unsigned char*,int) ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data, int len)
{
	struct sd *sd = (struct sd *) gspca_dev;
	unsigned char *sof;

	sof = cit_find_sof(gspca_dev, data, len);
	if (sof) {
		int n;

		/* finish decoding current frame */
		n = sof - data;
		if (n > sd->sof_len)
			n -= sd->sof_len;
		else
			n = 0;
		gspca_frame_add(gspca_dev, LAST_PACKET,
				data, n);
		gspca_frame_add(gspca_dev, FIRST_PACKET, NULL, 0);
		len -= sof - data;
		data = sof;
	}

	gspca_frame_add(gspca_dev, INTER_PACKET, data, len);
}