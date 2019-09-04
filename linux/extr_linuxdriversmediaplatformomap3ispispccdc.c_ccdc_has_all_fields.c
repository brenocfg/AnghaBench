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
struct isp_pipeline {int field; } ;
struct isp_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  entity; } ;
struct isp_ccdc_device {int /*<<< orphan*/  fields; TYPE_1__* formats; TYPE_2__ subdev; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_3__ {int field; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_FIELD_BOTH ; 
 int /*<<< orphan*/  CCDC_FIELD_BOTTOM ; 
 int /*<<< orphan*/  CCDC_FIELD_TOP ; 
 size_t CCDC_PAD_SOURCE_OF ; 
 int /*<<< orphan*/  ISPCCDC_SYN_MODE ; 
 int ISPCCDC_SYN_MODE_FLDSTAT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_CCDC ; 
 int V4L2_FIELD_ALTERNATE ; 
 int V4L2_FIELD_BOTTOM ; 
 int V4L2_FIELD_INTERLACED_BT ; 
 int V4L2_FIELD_INTERLACED_TB ; 
 int V4L2_FIELD_NONE ; 
 int V4L2_FIELD_TOP ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_ccdc_device*) ; 
 struct isp_pipeline* to_isp_pipeline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ccdc_has_all_fields(struct isp_ccdc_device *ccdc)
{
	struct isp_pipeline *pipe = to_isp_pipeline(&ccdc->subdev.entity);
	struct isp_device *isp = to_isp_device(ccdc);
	enum v4l2_field of_field = ccdc->formats[CCDC_PAD_SOURCE_OF].field;
	enum v4l2_field field;

	/* When the input is progressive fields don't matter. */
	if (of_field == V4L2_FIELD_NONE)
		return true;

	/* Read the current field identifier. */
	field = isp_reg_readl(isp, OMAP3_ISP_IOMEM_CCDC, ISPCCDC_SYN_MODE)
	      & ISPCCDC_SYN_MODE_FLDSTAT
	      ? V4L2_FIELD_BOTTOM : V4L2_FIELD_TOP;

	/* When capturing fields in alternate order just store the current field
	 * identifier in the pipeline.
	 */
	if (of_field == V4L2_FIELD_ALTERNATE) {
		pipe->field = field;
		return true;
	}

	/* The format is interlaced. Make sure we've captured both fields. */
	ccdc->fields |= field == V4L2_FIELD_BOTTOM
		      ? CCDC_FIELD_BOTTOM : CCDC_FIELD_TOP;

	if (ccdc->fields != CCDC_FIELD_BOTH)
		return false;

	/* Verify that the field just captured corresponds to the last field
	 * needed based on the desired field order.
	 */
	if ((of_field == V4L2_FIELD_INTERLACED_TB && field == V4L2_FIELD_TOP) ||
	    (of_field == V4L2_FIELD_INTERLACED_BT && field == V4L2_FIELD_BOTTOM))
		return false;

	/* The buffer can be completed, reset the fields for the next buffer. */
	ccdc->fields = 0;

	return true;
}