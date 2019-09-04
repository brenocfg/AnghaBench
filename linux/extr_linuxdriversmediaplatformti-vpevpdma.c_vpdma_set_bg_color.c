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
typedef  int /*<<< orphan*/  u32 ;
struct vpdma_data_format {scalar_t__ type; } ;
struct vpdma_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPDMA_BG_RGB ; 
 int /*<<< orphan*/  VPDMA_BG_YUV ; 
 scalar_t__ VPDMA_DATA_FMT_TYPE_RGB ; 
 scalar_t__ VPDMA_DATA_FMT_TYPE_YUV ; 
 int /*<<< orphan*/  write_reg (struct vpdma_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vpdma_set_bg_color(struct vpdma_data *vpdma,
		struct vpdma_data_format *fmt, u32 color)
{
	if (fmt->type == VPDMA_DATA_FMT_TYPE_RGB)
		write_reg(vpdma, VPDMA_BG_RGB, color);
	else if (fmt->type == VPDMA_DATA_FMT_TYPE_YUV)
		write_reg(vpdma, VPDMA_BG_YUV, color);
}