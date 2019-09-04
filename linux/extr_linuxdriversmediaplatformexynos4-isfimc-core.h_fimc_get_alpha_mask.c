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
struct fimc_fmt {int color; } ;

/* Variables and functions */
#define  FIMC_FMT_RGB444 130 
#define  FIMC_FMT_RGB555 129 
#define  FIMC_FMT_RGB888 128 

__attribute__((used)) static inline int fimc_get_alpha_mask(struct fimc_fmt *fmt)
{
	switch (fmt->color) {
	case FIMC_FMT_RGB444:	return 0x0f;
	case FIMC_FMT_RGB555:	return 0x01;
	case FIMC_FMT_RGB888:	return 0xff;
	default:		return 0;
	};
}