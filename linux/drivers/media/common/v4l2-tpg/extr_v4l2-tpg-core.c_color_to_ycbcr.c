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
struct tpg_data {scalar_t__ real_quantization; int real_ycbcr_enc; } ;

/* Variables and functions */
 int COEFF (double,int) ; 
 scalar_t__ V4L2_QUANTIZATION_FULL_RANGE ; 
#define  V4L2_YCBCR_ENC_601 134 
#define  V4L2_YCBCR_ENC_709 133 
#define  V4L2_YCBCR_ENC_BT2020 132 
#define  V4L2_YCBCR_ENC_BT2020_CONST_LUM 131 
#define  V4L2_YCBCR_ENC_SMPTE240M 130 
#define  V4L2_YCBCR_ENC_XV601 129 
#define  V4L2_YCBCR_ENC_XV709 128 
 int linear_to_rec709 (int) ; 
 int rec709_to_linear (int) ; 
 int /*<<< orphan*/  rgb2ycbcr (int const**,int,int,int,unsigned int,int*,int*,int*) ; 

__attribute__((used)) static void color_to_ycbcr(struct tpg_data *tpg, int r, int g, int b,
			   int *y, int *cb, int *cr)
{
#define COEFF(v, r) ((int)(0.5 + (v) * (r) * 256.0))

	static const int bt601[3][3] = {
		{ COEFF(0.299, 219),   COEFF(0.587, 219),   COEFF(0.114, 219)   },
		{ COEFF(-0.1687, 224), COEFF(-0.3313, 224), COEFF(0.5, 224)     },
		{ COEFF(0.5, 224),     COEFF(-0.4187, 224), COEFF(-0.0813, 224) },
	};
	static const int bt601_full[3][3] = {
		{ COEFF(0.299, 255),   COEFF(0.587, 255),   COEFF(0.114, 255)   },
		{ COEFF(-0.1687, 255), COEFF(-0.3313, 255), COEFF(0.5, 255)     },
		{ COEFF(0.5, 255),     COEFF(-0.4187, 255), COEFF(-0.0813, 255) },
	};
	static const int rec709[3][3] = {
		{ COEFF(0.2126, 219),  COEFF(0.7152, 219),  COEFF(0.0722, 219)  },
		{ COEFF(-0.1146, 224), COEFF(-0.3854, 224), COEFF(0.5, 224)     },
		{ COEFF(0.5, 224),     COEFF(-0.4542, 224), COEFF(-0.0458, 224) },
	};
	static const int rec709_full[3][3] = {
		{ COEFF(0.2126, 255),  COEFF(0.7152, 255),  COEFF(0.0722, 255)  },
		{ COEFF(-0.1146, 255), COEFF(-0.3854, 255), COEFF(0.5, 255)     },
		{ COEFF(0.5, 255),     COEFF(-0.4542, 255), COEFF(-0.0458, 255) },
	};
	static const int smpte240m[3][3] = {
		{ COEFF(0.212, 219),  COEFF(0.701, 219),  COEFF(0.087, 219)  },
		{ COEFF(-0.116, 224), COEFF(-0.384, 224), COEFF(0.5, 224)    },
		{ COEFF(0.5, 224),    COEFF(-0.445, 224), COEFF(-0.055, 224) },
	};
	static const int smpte240m_full[3][3] = {
		{ COEFF(0.212, 255),  COEFF(0.701, 255),  COEFF(0.087, 255)  },
		{ COEFF(-0.116, 255), COEFF(-0.384, 255), COEFF(0.5, 255)    },
		{ COEFF(0.5, 255),    COEFF(-0.445, 255), COEFF(-0.055, 255) },
	};
	static const int bt2020[3][3] = {
		{ COEFF(0.2627, 219),  COEFF(0.6780, 219),  COEFF(0.0593, 219)  },
		{ COEFF(-0.1396, 224), COEFF(-0.3604, 224), COEFF(0.5, 224)     },
		{ COEFF(0.5, 224),     COEFF(-0.4598, 224), COEFF(-0.0402, 224) },
	};
	static const int bt2020_full[3][3] = {
		{ COEFF(0.2627, 255),  COEFF(0.6780, 255),  COEFF(0.0593, 255)  },
		{ COEFF(-0.1396, 255), COEFF(-0.3604, 255), COEFF(0.5, 255)     },
		{ COEFF(0.5, 255),     COEFF(-0.4598, 255), COEFF(-0.0402, 255) },
	};
	static const int bt2020c[4] = {
		COEFF(1.0 / 1.9404, 224), COEFF(1.0 / 1.5816, 224),
		COEFF(1.0 / 1.7184, 224), COEFF(1.0 / 0.9936, 224),
	};
	static const int bt2020c_full[4] = {
		COEFF(1.0 / 1.9404, 255), COEFF(1.0 / 1.5816, 255),
		COEFF(1.0 / 1.7184, 255), COEFF(1.0 / 0.9936, 255),
	};

	bool full = tpg->real_quantization == V4L2_QUANTIZATION_FULL_RANGE;
	unsigned y_offset = full ? 0 : 16;
	int lin_y, yc;

	switch (tpg->real_ycbcr_enc) {
	case V4L2_YCBCR_ENC_601:
		rgb2ycbcr(full ? bt601_full : bt601, r, g, b, y_offset, y, cb, cr);
		break;
	case V4L2_YCBCR_ENC_XV601:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		rgb2ycbcr(bt601, r, g, b, 16, y, cb, cr);
		break;
	case V4L2_YCBCR_ENC_XV709:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		rgb2ycbcr(rec709, r, g, b, 16, y, cb, cr);
		break;
	case V4L2_YCBCR_ENC_BT2020:
		rgb2ycbcr(full ? bt2020_full : bt2020, r, g, b, y_offset, y, cb, cr);
		break;
	case V4L2_YCBCR_ENC_BT2020_CONST_LUM:
		lin_y = (COEFF(0.2627, 255) * rec709_to_linear(r) +
			 COEFF(0.6780, 255) * rec709_to_linear(g) +
			 COEFF(0.0593, 255) * rec709_to_linear(b)) >> 16;
		yc = linear_to_rec709(lin_y);
		*y = full ? yc : (yc * 219) / 255 + (16 << 4);
		if (b <= yc)
			*cb = (((b - yc) * (full ? bt2020c_full[0] : bt2020c[0])) >> 16) + (128 << 4);
		else
			*cb = (((b - yc) * (full ? bt2020c_full[1] : bt2020c[1])) >> 16) + (128 << 4);
		if (r <= yc)
			*cr = (((r - yc) * (full ? bt2020c_full[2] : bt2020c[2])) >> 16) + (128 << 4);
		else
			*cr = (((r - yc) * (full ? bt2020c_full[3] : bt2020c[3])) >> 16) + (128 << 4);
		break;
	case V4L2_YCBCR_ENC_SMPTE240M:
		rgb2ycbcr(full ? smpte240m_full : smpte240m, r, g, b, y_offset, y, cb, cr);
		break;
	case V4L2_YCBCR_ENC_709:
	default:
		rgb2ycbcr(full ? rec709_full : rec709, r, g, b, y_offset, y, cb, cr);
		break;
	}
}