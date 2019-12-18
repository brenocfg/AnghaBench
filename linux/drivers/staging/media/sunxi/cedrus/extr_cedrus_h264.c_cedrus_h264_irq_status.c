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
struct cedrus_dev {int dummy; } ;
struct cedrus_ctx {struct cedrus_dev* dev; } ;
typedef  enum cedrus_irq_status { ____Placeholder_cedrus_irq_status } cedrus_irq_status ;

/* Variables and functions */
 int CEDRUS_IRQ_ERROR ; 
 int CEDRUS_IRQ_NONE ; 
 int CEDRUS_IRQ_OK ; 
 int VE_H264_CTRL_SLICE_DECODE_INT ; 
 int /*<<< orphan*/  VE_H264_STATUS ; 
 int VE_H264_STATUS_DECODE_ERR_INT ; 
 int VE_H264_STATUS_VLD_DATA_REQ_INT ; 
 int cedrus_read (struct cedrus_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cedrus_irq_status
cedrus_h264_irq_status(struct cedrus_ctx *ctx)
{
	struct cedrus_dev *dev = ctx->dev;
	u32 reg = cedrus_read(dev, VE_H264_STATUS);

	if (reg & (VE_H264_STATUS_DECODE_ERR_INT |
		   VE_H264_STATUS_VLD_DATA_REQ_INT))
		return CEDRUS_IRQ_ERROR;

	if (reg & VE_H264_CTRL_SLICE_DECODE_INT)
		return CEDRUS_IRQ_OK;

	return CEDRUS_IRQ_NONE;
}