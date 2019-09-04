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
struct pxa_mbus_pixelfmt {scalar_t__ layout; int packing; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PXA_MBUS_LAYOUT_PACKED ; 
#define  PXA_MBUS_PACKING_2X8_PADHI 128 

__attribute__((used)) static s32 pxa_mbus_image_size(const struct pxa_mbus_pixelfmt *mf,
			u32 bytes_per_line, u32 height)
{
	if (mf->layout == PXA_MBUS_LAYOUT_PACKED)
		return bytes_per_line * height;

	switch (mf->packing) {
	case PXA_MBUS_PACKING_2X8_PADHI:
		return bytes_per_line * height * 2;
	default:
		return -EINVAL;
	}
}