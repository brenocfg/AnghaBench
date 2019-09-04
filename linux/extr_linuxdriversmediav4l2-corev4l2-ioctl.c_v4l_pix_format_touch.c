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
struct v4l2_pix_format {scalar_t__ xfer_func; scalar_t__ quantization; scalar_t__ ycbcr_enc; scalar_t__ flags; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_RAW ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 

__attribute__((used)) static void v4l_pix_format_touch(struct v4l2_pix_format *p)
{
	/*
	 * The v4l2_pix_format structure contains fields that make no sense for
	 * touch. Set them to default values in this case.
	 */

	p->field = V4L2_FIELD_NONE;
	p->colorspace = V4L2_COLORSPACE_RAW;
	p->flags = 0;
	p->ycbcr_enc = 0;
	p->quantization = 0;
	p->xfer_func = 0;
}