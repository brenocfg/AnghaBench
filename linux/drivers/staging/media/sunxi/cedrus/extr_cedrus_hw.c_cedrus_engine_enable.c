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
struct cedrus_dev {int dummy; } ;
typedef  enum cedrus_codec { ____Placeholder_cedrus_codec } cedrus_codec ;

/* Variables and functions */
#define  CEDRUS_CODEC_H264 129 
#define  CEDRUS_CODEC_MPEG2 128 
 int EINVAL ; 
 int /*<<< orphan*/  VE_MODE ; 
 int /*<<< orphan*/  VE_MODE_DDR_MODE_BW_128 ; 
 int /*<<< orphan*/  VE_MODE_DEC_H264 ; 
 int /*<<< orphan*/  VE_MODE_DEC_MPEG ; 
 int /*<<< orphan*/  VE_MODE_REC_WR_MODE_2MB ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cedrus_engine_enable(struct cedrus_dev *dev, enum cedrus_codec codec)
{
	u32 reg = 0;

	/*
	 * FIXME: This is only valid on 32-bits DDR's, we should test
	 * it on the A13/A33.
	 */
	reg |= VE_MODE_REC_WR_MODE_2MB;
	reg |= VE_MODE_DDR_MODE_BW_128;

	switch (codec) {
	case CEDRUS_CODEC_MPEG2:
		reg |= VE_MODE_DEC_MPEG;
		break;

	case CEDRUS_CODEC_H264:
		reg |= VE_MODE_DEC_H264;
		break;

	default:
		return -EINVAL;
	}

	cedrus_write(dev, VE_MODE, reg);

	return 0;
}