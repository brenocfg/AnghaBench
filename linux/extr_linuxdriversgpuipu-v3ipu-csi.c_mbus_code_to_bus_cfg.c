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
struct ipu_csi_bus_config {void* data_width; void* mipi_dt; void* data_fmt; } ;
typedef  enum v4l2_mbus_type { ____Placeholder_v4l2_mbus_type } v4l2_mbus_type ;

/* Variables and functions */
 void* CSI_SENS_CONF_DATA_FMT_BAYER ; 
 void* CSI_SENS_CONF_DATA_FMT_JPEG ; 
 void* CSI_SENS_CONF_DATA_FMT_RGB444 ; 
 void* CSI_SENS_CONF_DATA_FMT_RGB555 ; 
 void* CSI_SENS_CONF_DATA_FMT_RGB565 ; 
 void* CSI_SENS_CONF_DATA_FMT_RGB_YUV444 ; 
 void* CSI_SENS_CONF_DATA_FMT_YUV422_UYVY ; 
 void* CSI_SENS_CONF_DATA_FMT_YUV422_YUYV ; 
 int EINVAL ; 
 void* IPU_CSI_DATA_WIDTH_10 ; 
 void* IPU_CSI_DATA_WIDTH_12 ; 
 void* IPU_CSI_DATA_WIDTH_16 ; 
 void* IPU_CSI_DATA_WIDTH_8 ; 
#define  MEDIA_BUS_FMT_BGR565_2X8_BE 165 
#define  MEDIA_BUS_FMT_BGR565_2X8_LE 164 
#define  MEDIA_BUS_FMT_BGR888_1X24 163 
#define  MEDIA_BUS_FMT_JPEG_1X8 162 
#define  MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE 161 
#define  MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE 160 
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE 159 
#define  MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE 158 
#define  MEDIA_BUS_FMT_RGB565_2X8_BE 157 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 156 
#define  MEDIA_BUS_FMT_RGB888_1X24 155 
#define  MEDIA_BUS_FMT_SBGGR10_1X10 154 
#define  MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE 153 
#define  MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE 152 
#define  MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_BE 151 
#define  MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_LE 150 
#define  MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8 149 
#define  MEDIA_BUS_FMT_SBGGR12_1X12 148 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 147 
#define  MEDIA_BUS_FMT_SGBRG10_1X10 146 
#define  MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8 145 
#define  MEDIA_BUS_FMT_SGBRG12_1X12 144 
#define  MEDIA_BUS_FMT_SGBRG8_1X8 143 
#define  MEDIA_BUS_FMT_SGRBG10_1X10 142 
#define  MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 141 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 140 
#define  MEDIA_BUS_FMT_SGRBG8_1X8 139 
#define  MEDIA_BUS_FMT_SRGGB10_1X10 138 
#define  MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8 137 
#define  MEDIA_BUS_FMT_SRGGB12_1X12 136 
#define  MEDIA_BUS_FMT_SRGGB8_1X8 135 
#define  MEDIA_BUS_FMT_UYVY8_1X16 134 
#define  MEDIA_BUS_FMT_UYVY8_2X8 133 
#define  MEDIA_BUS_FMT_Y10_1X10 132 
#define  MEDIA_BUS_FMT_Y12_1X12 131 
#define  MEDIA_BUS_FMT_Y8_1X8 130 
#define  MEDIA_BUS_FMT_YUYV8_1X16 129 
#define  MEDIA_BUS_FMT_YUYV8_2X8 128 
 void* MIPI_DT_RAW10 ; 
 void* MIPI_DT_RAW12 ; 
 void* MIPI_DT_RAW8 ; 
 void* MIPI_DT_RGB444 ; 
 void* MIPI_DT_RGB555 ; 
 void* MIPI_DT_RGB565 ; 
 void* MIPI_DT_RGB888 ; 
 void* MIPI_DT_YUV422 ; 
 int V4L2_MBUS_CSI2 ; 

__attribute__((used)) static int mbus_code_to_bus_cfg(struct ipu_csi_bus_config *cfg, u32 mbus_code,
				enum v4l2_mbus_type mbus_type)
{
	switch (mbus_code) {
	case MEDIA_BUS_FMT_BGR565_2X8_BE:
	case MEDIA_BUS_FMT_BGR565_2X8_LE:
	case MEDIA_BUS_FMT_RGB565_2X8_BE:
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
		if (mbus_type == V4L2_MBUS_CSI2)
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB565;
		else
			cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RGB565;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_RGB444_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_RGB444_2X8_PADHI_LE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB444;
		cfg->mipi_dt = MIPI_DT_RGB444;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_RGB555_2X8_PADHI_LE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB555;
		cfg->mipi_dt = MIPI_DT_RGB555;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_RGB888_1X24:
	case MEDIA_BUS_FMT_BGR888_1X24:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_RGB_YUV444;
		cfg->mipi_dt = MIPI_DT_RGB888;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_UYVY8_2X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_UYVY;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_YUYV8_2X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_YUV422_YUYV;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_YUYV8_1X16:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_YUV422;
		cfg->data_width = IPU_CSI_DATA_WIDTH_16;
		break;
	case MEDIA_BUS_FMT_SBGGR8_1X8:
	case MEDIA_BUS_FMT_SGBRG8_1X8:
	case MEDIA_BUS_FMT_SGRBG8_1X8:
	case MEDIA_BUS_FMT_SRGGB8_1X8:
	case MEDIA_BUS_FMT_Y8_1X8:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW8;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_SBGGR10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGBRG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SRGGB10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_BE:
	case MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE:
	case MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_BE:
	case MEDIA_BUS_FMT_SBGGR10_2X8_PADLO_LE:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW10;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	case MEDIA_BUS_FMT_SBGGR10_1X10:
	case MEDIA_BUS_FMT_SGBRG10_1X10:
	case MEDIA_BUS_FMT_SGRBG10_1X10:
	case MEDIA_BUS_FMT_SRGGB10_1X10:
	case MEDIA_BUS_FMT_Y10_1X10:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW10;
		cfg->data_width = IPU_CSI_DATA_WIDTH_10;
		break;
	case MEDIA_BUS_FMT_SBGGR12_1X12:
	case MEDIA_BUS_FMT_SGBRG12_1X12:
	case MEDIA_BUS_FMT_SGRBG12_1X12:
	case MEDIA_BUS_FMT_SRGGB12_1X12:
	case MEDIA_BUS_FMT_Y12_1X12:
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_BAYER;
		cfg->mipi_dt = MIPI_DT_RAW12;
		cfg->data_width = IPU_CSI_DATA_WIDTH_12;
		break;
	case MEDIA_BUS_FMT_JPEG_1X8:
		/* TODO */
		cfg->data_fmt = CSI_SENS_CONF_DATA_FMT_JPEG;
		cfg->mipi_dt = MIPI_DT_RAW8;
		cfg->data_width = IPU_CSI_DATA_WIDTH_8;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}