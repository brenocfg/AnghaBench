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
typedef  int /*<<< orphan*/  wmem ;
struct wiimote_data {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
#define  WIIMOTE_EXT_CLASSIC_CONTROLLER 131 
#define  WIIMOTE_EXT_DRUMS 130 
#define  WIIMOTE_EXT_GUITAR 129 
#define  WIIMOTE_EXT_NUNCHUK 128 
 int wiimote_cmd_write (struct wiimote_data*,int,int*,int) ; 

__attribute__((used)) static bool wiimote_cmd_map_mp(struct wiimote_data *wdata, __u8 exttype)
{
	__u8 wmem;

	/* map MP with correct pass-through mode */
	switch (exttype) {
	case WIIMOTE_EXT_CLASSIC_CONTROLLER:
	case WIIMOTE_EXT_DRUMS:
	case WIIMOTE_EXT_GUITAR:
		wmem = 0x07;
		break;
	case WIIMOTE_EXT_NUNCHUK:
		wmem = 0x05;
		break;
	default:
		wmem = 0x04;
		break;
	}

	return wiimote_cmd_write(wdata, 0xa600fe, &wmem, sizeof(wmem));
}