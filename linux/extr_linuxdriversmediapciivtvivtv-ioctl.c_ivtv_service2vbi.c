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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_SLICED_TYPE_CAPTION_525 ; 
 int /*<<< orphan*/  IVTV_SLICED_TYPE_TELETEXT_B ; 
 int /*<<< orphan*/  IVTV_SLICED_TYPE_VPS ; 
 int /*<<< orphan*/  IVTV_SLICED_TYPE_WSS_625 ; 
#define  V4L2_SLICED_CAPTION_525 131 
#define  V4L2_SLICED_TELETEXT_B 130 
#define  V4L2_SLICED_VPS 129 
#define  V4L2_SLICED_WSS_625 128 

u16 ivtv_service2vbi(int type)
{
	switch (type) {
		case V4L2_SLICED_TELETEXT_B:
			return IVTV_SLICED_TYPE_TELETEXT_B;
		case V4L2_SLICED_CAPTION_525:
			return IVTV_SLICED_TYPE_CAPTION_525;
		case V4L2_SLICED_WSS_625:
			return IVTV_SLICED_TYPE_WSS_625;
		case V4L2_SLICED_VPS:
			return IVTV_SLICED_TYPE_VPS;
		default:
			return 0;
	}
}