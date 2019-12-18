#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct m5mols_exif {int /*<<< orphan*/  qval; int /*<<< orphan*/  sdr; int /*<<< orphan*/  flash; int /*<<< orphan*/  iso_speed; int /*<<< orphan*/  exposure_bias; int /*<<< orphan*/  brightness; int /*<<< orphan*/  aperture; int /*<<< orphan*/  shutter_speed; int /*<<< orphan*/  exposure_time; } ;
struct TYPE_2__ {scalar_t__ thumb; scalar_t__ main; scalar_t__ total; struct m5mols_exif exif; } ;
struct m5mols_info {TYPE_1__ cap; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPC_IMAGE_SIZE ; 
 int /*<<< orphan*/  CAPC_THUMB_SIZE ; 
 int /*<<< orphan*/  EXIF_INFO_AV_DE ; 
 int /*<<< orphan*/  EXIF_INFO_AV_NU ; 
 int /*<<< orphan*/  EXIF_INFO_BV_DE ; 
 int /*<<< orphan*/  EXIF_INFO_BV_NU ; 
 int /*<<< orphan*/  EXIF_INFO_EBV_DE ; 
 int /*<<< orphan*/  EXIF_INFO_EBV_NU ; 
 int /*<<< orphan*/  EXIF_INFO_EXPTIME_DE ; 
 int /*<<< orphan*/  EXIF_INFO_EXPTIME_NU ; 
 int /*<<< orphan*/  EXIF_INFO_FLASH ; 
 int /*<<< orphan*/  EXIF_INFO_ISO ; 
 int /*<<< orphan*/  EXIF_INFO_QVAL ; 
 int /*<<< orphan*/  EXIF_INFO_SDR ; 
 int /*<<< orphan*/  EXIF_INFO_TV_DE ; 
 int /*<<< orphan*/  EXIF_INFO_TV_NU ; 
 int m5mols_read_rational (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int m5mols_read_u16 (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int m5mols_read_u32 (struct v4l2_subdev*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int m5mols_capture_info(struct m5mols_info *info)
{
	struct m5mols_exif *exif = &info->cap.exif;
	struct v4l2_subdev *sd = &info->sd;
	int ret;

	ret = m5mols_read_rational(sd, EXIF_INFO_EXPTIME_NU,
				   EXIF_INFO_EXPTIME_DE, &exif->exposure_time);
	if (ret)
		return ret;
	ret = m5mols_read_rational(sd, EXIF_INFO_TV_NU, EXIF_INFO_TV_DE,
				   &exif->shutter_speed);
	if (ret)
		return ret;
	ret = m5mols_read_rational(sd, EXIF_INFO_AV_NU, EXIF_INFO_AV_DE,
				   &exif->aperture);
	if (ret)
		return ret;
	ret = m5mols_read_rational(sd, EXIF_INFO_BV_NU, EXIF_INFO_BV_DE,
				   &exif->brightness);
	if (ret)
		return ret;
	ret = m5mols_read_rational(sd, EXIF_INFO_EBV_NU, EXIF_INFO_EBV_DE,
				   &exif->exposure_bias);
	if (ret)
		return ret;

	ret = m5mols_read_u16(sd, EXIF_INFO_ISO, &exif->iso_speed);
	if (!ret)
		ret = m5mols_read_u16(sd, EXIF_INFO_FLASH, &exif->flash);
	if (!ret)
		ret = m5mols_read_u16(sd, EXIF_INFO_SDR, &exif->sdr);
	if (!ret)
		ret = m5mols_read_u16(sd, EXIF_INFO_QVAL, &exif->qval);
	if (ret)
		return ret;

	if (!ret)
		ret = m5mols_read_u32(sd, CAPC_IMAGE_SIZE, &info->cap.main);
	if (!ret)
		ret = m5mols_read_u32(sd, CAPC_THUMB_SIZE, &info->cap.thumb);
	if (!ret)
		info->cap.total = info->cap.main + info->cap.thumb;

	return ret;
}