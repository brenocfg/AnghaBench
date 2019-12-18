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
struct uvc_control_mapping {int offset; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int const s32 ;

/* Variables and functions */
#define  UVC_GET_CUR 132 
#define  UVC_GET_DEF 131 
#define  UVC_GET_MAX 130 
#define  UVC_GET_MIN 129 
#define  UVC_GET_RES 128 

__attribute__((used)) static s32 uvc_ctrl_get_rel_speed(struct uvc_control_mapping *mapping,
	u8 query, const u8 *data)
{
	unsigned int first = mapping->offset / 8;
	s8 rel = (s8)data[first];

	switch (query) {
	case UVC_GET_CUR:
		return (rel == 0) ? 0 : (rel > 0 ? data[first+1]
						 : -data[first+1]);
	case UVC_GET_MIN:
		return -data[first+1];
	case UVC_GET_MAX:
	case UVC_GET_RES:
	case UVC_GET_DEF:
	default:
		return data[first+1];
	}
}