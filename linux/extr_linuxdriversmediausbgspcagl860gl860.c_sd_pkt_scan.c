#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sd {int swapRB; int nbIm; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {TYPE_2__ cam; int /*<<< orphan*/  curr_mode; } ;
typedef  size_t s32 ;
typedef  int s16 ;
struct TYPE_3__ {int bytesperline; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_PACKET ; 
 int /*<<< orphan*/  INTER_PACKET ; 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sd_pkt_scan(struct gspca_dev *gspca_dev,
			u8 *data, int len)
{
	struct sd *sd = (struct sd *) gspca_dev;
	static s32 nSkipped;

	s32 mode = (s32) gspca_dev->curr_mode;
	s32 nToSkip =
		sd->swapRB * (gspca_dev->cam.cam_mode[mode].bytesperline + 1);

	/* Test only against 0202h, so endianness does not matter */
	switch (*(s16 *) data) {
	case 0x0202:		/* End of frame, start a new one */
		gspca_frame_add(gspca_dev, LAST_PACKET, NULL, 0);
		nSkipped = 0;
		if (sd->nbIm >= 0 && sd->nbIm < 10)
			sd->nbIm++;
		gspca_frame_add(gspca_dev, FIRST_PACKET, NULL, 0);
		break;

	default:
		data += 2;
		len  -= 2;
		if (nSkipped + len <= nToSkip)
			nSkipped += len;
		else {
			if (nSkipped < nToSkip && nSkipped + len > nToSkip) {
				data += nToSkip - nSkipped;
				len  -= nToSkip - nSkipped;
				nSkipped = nToSkip + 1;
			}
			gspca_frame_add(gspca_dev,
				INTER_PACKET, data, len);
		}
		break;
	}
}