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

/* Variables and functions */
#define  UVC_GET_CUR 135 
#define  UVC_GET_DEF 134 
#define  UVC_GET_INFO 133 
#define  UVC_GET_LEN 132 
#define  UVC_GET_MAX 131 
#define  UVC_GET_MIN 130 
#define  UVC_GET_RES 129 
#define  UVC_SET_CUR 128 

__attribute__((used)) static const char *uvc_query_name(u8 query)
{
	switch (query) {
	case UVC_SET_CUR:
		return "SET_CUR";
	case UVC_GET_CUR:
		return "GET_CUR";
	case UVC_GET_MIN:
		return "GET_MIN";
	case UVC_GET_MAX:
		return "GET_MAX";
	case UVC_GET_RES:
		return "GET_RES";
	case UVC_GET_LEN:
		return "GET_LEN";
	case UVC_GET_INFO:
		return "GET_INFO";
	case UVC_GET_DEF:
		return "GET_DEF";
	default:
		return "<invalid>";
	}
}