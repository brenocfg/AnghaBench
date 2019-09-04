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
struct isc_format {int fourcc; } ;
struct fmt_config {int /*<<< orphan*/  dcfg_imode; int /*<<< orphan*/  rlp_cfg_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_DCFG_IMODE_PACKED8 ; 
 int /*<<< orphan*/  ISC_DCFG_YMBSIZE_BEATS8 ; 
 int /*<<< orphan*/  ISC_RLP_CFG_MODE_DAT8 ; 
#define  V4L2_PIX_FMT_SBGGR10 135 
#define  V4L2_PIX_FMT_SBGGR12 134 
#define  V4L2_PIX_FMT_SGBRG10 133 
#define  V4L2_PIX_FMT_SGBRG12 132 
#define  V4L2_PIX_FMT_SGRBG10 131 
#define  V4L2_PIX_FMT_SGRBG12 130 
#define  V4L2_PIX_FMT_SRGGB10 129 
#define  V4L2_PIX_FMT_SRGGB12 128 
 struct fmt_config* get_fmt_config (int) ; 

__attribute__((used)) static inline void isc_get_param(const struct isc_format *fmt,
				 u32 *rlp_mode, u32 *dcfg)
{
	struct fmt_config *config = get_fmt_config(fmt->fourcc);

	*dcfg = ISC_DCFG_YMBSIZE_BEATS8;

	switch (fmt->fourcc) {
	case V4L2_PIX_FMT_SBGGR10:
	case V4L2_PIX_FMT_SGBRG10:
	case V4L2_PIX_FMT_SGRBG10:
	case V4L2_PIX_FMT_SRGGB10:
	case V4L2_PIX_FMT_SBGGR12:
	case V4L2_PIX_FMT_SGBRG12:
	case V4L2_PIX_FMT_SGRBG12:
	case V4L2_PIX_FMT_SRGGB12:
		*rlp_mode = config->rlp_cfg_mode;
		*dcfg |= config->dcfg_imode;
		break;
	default:
		*rlp_mode = ISC_RLP_CFG_MODE_DAT8;
		*dcfg |= ISC_DCFG_IMODE_PACKED8;
		break;
	}
}