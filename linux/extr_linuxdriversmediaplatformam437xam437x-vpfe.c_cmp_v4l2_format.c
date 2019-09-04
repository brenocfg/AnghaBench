#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; scalar_t__ pixelformat; scalar_t__ field; scalar_t__ colorspace; scalar_t__ ycbcr_enc; scalar_t__ quantization; scalar_t__ xfer_func; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {scalar_t__ type; TYPE_2__ fmt; } ;

/* Variables and functions */

__attribute__((used)) static int
cmp_v4l2_format(const struct v4l2_format *lhs, const struct v4l2_format *rhs)
{
	return lhs->type == rhs->type &&
		lhs->fmt.pix.width == rhs->fmt.pix.width &&
		lhs->fmt.pix.height == rhs->fmt.pix.height &&
		lhs->fmt.pix.pixelformat == rhs->fmt.pix.pixelformat &&
		lhs->fmt.pix.field == rhs->fmt.pix.field &&
		lhs->fmt.pix.colorspace == rhs->fmt.pix.colorspace &&
		lhs->fmt.pix.ycbcr_enc == rhs->fmt.pix.ycbcr_enc &&
		lhs->fmt.pix.quantization == rhs->fmt.pix.quantization &&
		lhs->fmt.pix.xfer_func == rhs->fmt.pix.xfer_func;
}