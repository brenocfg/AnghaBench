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
typedef  int u32 ;

/* Variables and functions */
 int IPU_DC_MAP_BGR24 ; 
 int IPU_DC_MAP_BGR666 ; 
 int IPU_DC_MAP_GBR24 ; 
 int IPU_DC_MAP_LVDS666 ; 
 int IPU_DC_MAP_RGB24 ; 
 int IPU_DC_MAP_RGB565 ; 
#define  MEDIA_BUS_FMT_BGR888_1X24 133 
#define  MEDIA_BUS_FMT_GBR888_1X24 132 
#define  MEDIA_BUS_FMT_RGB565_1X16 131 
#define  MEDIA_BUS_FMT_RGB666_1X18 130 
#define  MEDIA_BUS_FMT_RGB666_1X24_CPADHI 129 
#define  MEDIA_BUS_FMT_RGB888_1X24 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static int ipu_bus_format_to_map(u32 fmt)
{
	switch (fmt) {
	default:
		WARN_ON(1);
		/* fall-through */
	case MEDIA_BUS_FMT_RGB888_1X24:
		return IPU_DC_MAP_RGB24;
	case MEDIA_BUS_FMT_RGB565_1X16:
		return IPU_DC_MAP_RGB565;
	case MEDIA_BUS_FMT_GBR888_1X24:
		return IPU_DC_MAP_GBR24;
	case MEDIA_BUS_FMT_RGB666_1X18:
		return IPU_DC_MAP_BGR666;
	case MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
		return IPU_DC_MAP_LVDS666;
	case MEDIA_BUS_FMT_BGR888_1X24:
		return IPU_DC_MAP_BGR24;
	}
}