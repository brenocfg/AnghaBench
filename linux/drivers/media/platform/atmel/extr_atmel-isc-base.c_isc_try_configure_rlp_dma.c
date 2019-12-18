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
struct TYPE_2__ {int bpp; int fourcc; void* dctrl_dview; void* dcfg_imode; void* rlp_cfg_mode; } ;
struct isc_device {TYPE_1__ try_config; } ;

/* Variables and functions */
 int EINVAL ; 
 void* ISC_DCFG_IMODE_PACKED16 ; 
 void* ISC_DCFG_IMODE_PACKED32 ; 
 void* ISC_DCFG_IMODE_PACKED8 ; 
 void* ISC_DCFG_IMODE_YC420P ; 
 void* ISC_DCFG_IMODE_YC422P ; 
 void* ISC_DCTRL_DVIEW_PACKED ; 
 void* ISC_DCTRL_DVIEW_PLANAR ; 
 void* ISC_RLP_CFG_MODE_ARGB32 ; 
 void* ISC_RLP_CFG_MODE_ARGB444 ; 
 void* ISC_RLP_CFG_MODE_ARGB555 ; 
 void* ISC_RLP_CFG_MODE_DAT10 ; 
 void* ISC_RLP_CFG_MODE_DAT12 ; 
 void* ISC_RLP_CFG_MODE_DAT8 ; 
 void* ISC_RLP_CFG_MODE_DATY8 ; 
 void* ISC_RLP_CFG_MODE_RGB565 ; 
 void* ISC_RLP_CFG_MODE_YYCC ; 
#define  V4L2_PIX_FMT_ABGR32 148 
#define  V4L2_PIX_FMT_ARGB444 147 
#define  V4L2_PIX_FMT_ARGB555 146 
#define  V4L2_PIX_FMT_GREY 145 
#define  V4L2_PIX_FMT_RGB565 144 
#define  V4L2_PIX_FMT_SBGGR10 143 
#define  V4L2_PIX_FMT_SBGGR12 142 
#define  V4L2_PIX_FMT_SBGGR8 141 
#define  V4L2_PIX_FMT_SGBRG10 140 
#define  V4L2_PIX_FMT_SGBRG12 139 
#define  V4L2_PIX_FMT_SGBRG8 138 
#define  V4L2_PIX_FMT_SGRBG10 137 
#define  V4L2_PIX_FMT_SGRBG12 136 
#define  V4L2_PIX_FMT_SGRBG8 135 
#define  V4L2_PIX_FMT_SRGGB10 134 
#define  V4L2_PIX_FMT_SRGGB12 133 
#define  V4L2_PIX_FMT_SRGGB8 132 
#define  V4L2_PIX_FMT_XBGR32 131 
#define  V4L2_PIX_FMT_YUV420 130 
#define  V4L2_PIX_FMT_YUV422P 129 
#define  V4L2_PIX_FMT_YUYV 128 

__attribute__((used)) static int isc_try_configure_rlp_dma(struct isc_device *isc, bool direct_dump)
{
	if (direct_dump) {
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT8;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		return 0;
	}

	switch (isc->try_config.fourcc) {
	case V4L2_PIX_FMT_SBGGR8:
	case V4L2_PIX_FMT_SGBRG8:
	case V4L2_PIX_FMT_SGRBG8:
	case V4L2_PIX_FMT_SRGGB8:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT8;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 8;
		break;
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SRGGB10:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT10;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		break;
	case V4L2_PIX_FMT_SBGGR12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SRGGB12:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DAT12;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		break;
	case V4L2_PIX_FMT_RGB565:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_RGB565;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		break;
	case V4L2_PIX_FMT_ARGB444:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_ARGB444;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		break;
	case V4L2_PIX_FMT_ARGB555:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_ARGB555;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED16;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		break;
	case V4L2_PIX_FMT_ABGR32:
	case V4L2_PIX_FMT_XBGR32:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_ARGB32;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 32;
		break;
	case V4L2_PIX_FMT_YUV420:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_YYCC;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_YC420P;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PLANAR;
		isc->try_config.bpp = 12;
		break;
	case V4L2_PIX_FMT_YUV422P:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_YYCC;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_YC422P;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PLANAR;
		isc->try_config.bpp = 16;
		break;
	case V4L2_PIX_FMT_YUYV:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_YYCC;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED32;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 16;
		break;
	case V4L2_PIX_FMT_GREY:
		isc->try_config.rlp_cfg_mode = ISC_RLP_CFG_MODE_DATY8;
		isc->try_config.dcfg_imode = ISC_DCFG_IMODE_PACKED8;
		isc->try_config.dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
		isc->try_config.bpp = 8;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}