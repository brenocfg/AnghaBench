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
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;

/* Variables and functions */
 int OMAP_BO_TILED ; 
#define  OMAP_BO_TILED_16 130 
#define  OMAP_BO_TILED_32 129 
#define  OMAP_BO_TILED_8 128 
 int TILFMT_16BIT ; 
 int TILFMT_32BIT ; 
 int TILFMT_8BIT ; 
 int TILFMT_PAGE ; 

__attribute__((used)) static inline enum tiler_fmt gem2fmt(u32 flags)
{
	switch (flags & OMAP_BO_TILED) {
	case OMAP_BO_TILED_8:
		return TILFMT_8BIT;
	case OMAP_BO_TILED_16:
		return TILFMT_16BIT;
	case OMAP_BO_TILED_32:
		return TILFMT_32BIT;
	default:
		return TILFMT_PAGE;
	}
}