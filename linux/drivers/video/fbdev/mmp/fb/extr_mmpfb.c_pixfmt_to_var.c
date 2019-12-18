#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {int offset; int length; } ;
struct TYPE_6__ {int offset; int length; } ;
struct TYPE_5__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;

/* Variables and functions */
#define  PIXFMT_BGR565 143 
#define  PIXFMT_BGR888PACK 142 
#define  PIXFMT_BGR888UNPACK 141 
#define  PIXFMT_BGRA888 140 
#define  PIXFMT_PSEUDOCOLOR 139 
#define  PIXFMT_RGB565 138 
#define  PIXFMT_RGB888PACK 137 
#define  PIXFMT_RGB888UNPACK 136 
#define  PIXFMT_RGBA888 135 
#define  PIXFMT_UYVY 134 
#define  PIXFMT_VYUY 133 
#define  PIXFMT_YUV420P 132 
#define  PIXFMT_YUV422P 131 
#define  PIXFMT_YUYV 130 
#define  PIXFMT_YVU420P 129 
#define  PIXFMT_YVU422P 128 

__attribute__((used)) static void pixfmt_to_var(struct fb_var_screeninfo *var, int pix_fmt)
{
	switch (pix_fmt) {
	case PIXFMT_RGB565:
		var->bits_per_pixel = 16;
		var->red.offset = 11;	var->red.length = 5;
		var->green.offset = 5;   var->green.length = 6;
		var->blue.offset = 0;	var->blue.length = 5;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_BGR565:
		var->bits_per_pixel = 16;
		var->red.offset = 0;	var->red.length = 5;
		var->green.offset = 5;	 var->green.length = 6;
		var->blue.offset = 11;	var->blue.length = 5;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_RGB888UNPACK:
		var->bits_per_pixel = 32;
		var->red.offset = 16;	var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_BGR888UNPACK:
		var->bits_per_pixel = 32;
		var->red.offset = 0;	var->red.length = 8;
		var->green.offset = 8;	 var->green.length = 8;
		var->blue.offset = 16;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_RGBA888:
		var->bits_per_pixel = 32;
		var->red.offset = 16;	var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 24; var->transp.length = 8;
		break;
	case PIXFMT_BGRA888:
		var->bits_per_pixel = 32;
		var->red.offset = 0;	var->red.length = 8;
		var->green.offset = 8;	 var->green.length = 8;
		var->blue.offset = 16;	var->blue.length = 8;
		var->transp.offset = 24; var->transp.length = 8;
		break;
	case PIXFMT_RGB888PACK:
		var->bits_per_pixel = 24;
		var->red.offset = 16;	var->red.length = 8;
		var->green.offset = 8;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_BGR888PACK:
		var->bits_per_pixel = 24;
		var->red.offset = 0;	var->red.length = 8;
		var->green.offset = 8;	 var->green.length = 8;
		var->blue.offset = 16;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_YUV420P:
		var->bits_per_pixel = 12;
		var->red.offset = 4;	 var->red.length = 8;
		var->green.offset = 2;   var->green.length = 2;
		var->blue.offset = 0;   var->blue.length = 2;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_YVU420P:
		var->bits_per_pixel = 12;
		var->red.offset = 4;	 var->red.length = 8;
		var->green.offset = 0;	 var->green.length = 2;
		var->blue.offset = 2;	var->blue.length = 2;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_YUV422P:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 8;
		var->green.offset = 4;   var->green.length = 4;
		var->blue.offset = 0;   var->blue.length = 4;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_YVU422P:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 8;
		var->green.offset = 0;	 var->green.length = 4;
		var->blue.offset = 4;	var->blue.length = 4;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_UYVY:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 16;
		var->green.offset = 4;   var->green.length = 16;
		var->blue.offset = 0;   var->blue.length = 16;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_VYUY:
		var->bits_per_pixel = 16;
		var->red.offset = 8;	 var->red.length = 16;
		var->green.offset = 0;	 var->green.length = 16;
		var->blue.offset = 4;	var->blue.length = 16;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_YUYV:
		var->bits_per_pixel = 16;
		var->red.offset = 0;	 var->red.length = 16;
		var->green.offset = 4;	 var->green.length = 16;
		var->blue.offset = 8;	var->blue.length = 16;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	case PIXFMT_PSEUDOCOLOR:
		var->bits_per_pixel = 8;
		var->red.offset = 0;	 var->red.length = 8;
		var->green.offset = 0;   var->green.length = 8;
		var->blue.offset = 0;	var->blue.length = 8;
		var->transp.offset = 0;  var->transp.length = 0;
		break;
	}
}