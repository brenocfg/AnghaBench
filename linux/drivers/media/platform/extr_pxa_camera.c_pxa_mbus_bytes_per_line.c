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
struct pxa_mbus_pixelfmt {scalar_t__ layout; int bits_per_sample; int packing; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PXA_MBUS_LAYOUT_PACKED ; 
#define  PXA_MBUS_PACKING_2X8_PADHI 130 
#define  PXA_MBUS_PACKING_EXTEND16 129 
#define  PXA_MBUS_PACKING_NONE 128 

__attribute__((used)) static s32 pxa_mbus_bytes_per_line(u32 width, const struct pxa_mbus_pixelfmt *mf)
{
	if (mf->layout != PXA_MBUS_LAYOUT_PACKED)
		return width * mf->bits_per_sample / 8;

	switch (mf->packing) {
	case PXA_MBUS_PACKING_NONE:
		return width * mf->bits_per_sample / 8;
	case PXA_MBUS_PACKING_2X8_PADHI:
	case PXA_MBUS_PACKING_EXTEND16:
		return width * 2;
	}
	return -EINVAL;
}