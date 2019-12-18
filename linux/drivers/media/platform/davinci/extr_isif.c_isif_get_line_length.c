#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; } ;
struct TYPE_7__ {TYPE_1__ win; } ;
struct TYPE_9__ {unsigned int width; } ;
struct TYPE_8__ {TYPE_4__ win; } ;
struct TYPE_10__ {scalar_t__ if_type; scalar_t__ data_pack; TYPE_2__ ycbcr; TYPE_3__ bayer; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 scalar_t__ ISIF_PACK_12BIT ; 
 scalar_t__ ISIF_PACK_8BIT ; 
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_5__ isif_cfg ; 

__attribute__((used)) static unsigned int isif_get_line_length(void)
{
	unsigned int len;

	if (isif_cfg.if_type == VPFE_RAW_BAYER) {
		if (isif_cfg.data_pack == ISIF_PACK_8BIT)
			len = ((isif_cfg.bayer.win.width));
		else if (isif_cfg.data_pack == ISIF_PACK_12BIT)
			len = (((isif_cfg.bayer.win.width * 2) +
				 (isif_cfg.bayer.win.width >> 2)));
		else
			len = (((isif_cfg.bayer.win.width * 2)));
	} else
		len = (((isif_cfg.ycbcr.win.width * 2)));
	return ALIGN(len, 32);
}