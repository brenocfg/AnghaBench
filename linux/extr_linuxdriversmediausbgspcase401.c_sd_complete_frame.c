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
typedef  int /*<<< orphan*/  u8 ;
struct sd {int expo_change_state; } ;
struct gspca_dev {int /*<<< orphan*/  last_packet_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_PACKET ; 
#define  EXPO_CHANGED 130 
#define  EXPO_DROP_FRAME 129 
#define  EXPO_NO_CHANGE 128 
 int /*<<< orphan*/  LAST_PACKET ; 
 int /*<<< orphan*/  gspca_frame_add (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sd_complete_frame(struct gspca_dev *gspca_dev, u8 *data, int len)
{
	struct sd *sd = (struct sd *)gspca_dev;

	switch (sd->expo_change_state) {
	case EXPO_CHANGED:
		/* The exposure was changed while this frame
		   was being send, so this frame is ok */
		sd->expo_change_state = EXPO_DROP_FRAME;
		break;
	case EXPO_DROP_FRAME:
		/* The exposure was changed while this frame
		   was being captured, drop it! */
		gspca_dev->last_packet_type = DISCARD_PACKET;
		sd->expo_change_state = EXPO_NO_CHANGE;
		break;
	case EXPO_NO_CHANGE:
		break;
	}
	gspca_frame_add(gspca_dev, LAST_PACKET, data, len);
}