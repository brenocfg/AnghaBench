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
 int /*<<< orphan*/  ycbcr2rgb (int const**,int,int,int,unsigned int,int*,int*,int*) ; 

__attribute__((used)) static void ycbcr_to_color(struct tpg_data *tpg, int y, int cb, int cr,
			   int *r, int *g, int *b)
{
#undef COEFF
#define COEFF(v, r) ((int)(0.5 + (v) * ((255.0 * 255.0 * 16.0) / (r))))
	static const int bt601[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.4020, 224)  },
		{ COEFF(1, 219), COEFF(-0.3441, 224), COEFF(-0.7141, 224) },
		{ COEFF(1, 219), COEFF(1.7720, 224),  COEFF(0, 224)       },
	};
	static const int bt601_full[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.4020, 255)  },
		{ COEFF(1, 255), COEFF(-0.3441, 255), COEFF(-0.7141, 255) },
		{ COEFF(1, 255), COEFF(1.7720, 255),  COEFF(0, 255)       },
	};
	static const int rec709[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.5748, 224)  },
		{ COEFF(1, 219), COEFF(-0.1873, 224), COEFF(-0.4681, 224) },
		{ COEFF(1, 219), COEFF(1.8556, 224),  COEFF(0, 224)       },
	};
	static const int rec709_full[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.5748, 255)  },
		{ COEFF(1, 255), COEFF(-0.1873, 255), COEFF(-0.4681, 255) },
		{ COEFF(1, 255), COEFF(1.8556, 255),  COEFF(0, 255)       },
	};
	static const int smpte240m[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.5756, 224)  },
		{ COEFF(1, 219), COEFF(-0.2253, 224), COEFF(-0.4767, 224) },
		{ COEFF(1, 219), COEFF(1.8270, 224),  COEFF(0, 224)       },
	};
	static const int smpte240m_full[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.5756, 255)  },
		{ COEFF(1, 255), COEFF(-0.2253, 255), COEFF(-0.4767, 255) },
		{ COEFF(1, 255), COEFF(1.8270, 255),  COEFF(0, 255)       },
	};
	static const int bt2020[3][3] = {
		{ COEFF(1, 219), COEFF(0, 224),       COEFF(1.4746, 224)  },
		{ COEFF(1, 219), COEFF(-0.1646, 224), COEFF(-0.5714, 224) },
		{ COEFF(1, 219), COEFF(1.8814, 224),  COEFF(0, 224)       },
	};
	static const int bt2020_full[3][3] = {
		{ COEFF(1, 255), COEFF(0, 255),       COEFF(1.4746, 255)  },
		{ COEFF(1, 255), COEFF(-0.1646, 255), COEFF(-0.5714, 255) },
		{ COEFF(1, 255), COEFF(1.8814, 255),  COEFF(0, 255)       },
	};
	static const int bt2020c[4] = {
		COEFF(1.9404, 224), COEFF(1.5816, 224),
		COEFF(1.7184, 224), COEFF(0.9936, 224),
	};
	static const int bt2020c_full[4] = {
		COEFF(1.9404, 255), COEFF(1.5816, 255),
		COEFF(1.7184, 255), COEFF(0.9936, 255),
	};

	bool full = tpg->real_quantization == V4L2_QUANTIZATION_FULL_RANGE;
	unsigned y_offset = full ? 0 : 16;
	int y_fac = full ? COEFF(1.0, 255) : COEFF(1.0, 219);
	int lin_r, lin_g, lin_b, lin_y;

	switch (tpg->real_ycbcr_enc) {
	case V4L2_YCBCR_ENC_601:
		ycbcr2rgb(full ? bt601_full : bt601, y, cb, cr, y_offset, r, g, b);
		break;
	case V4L2_YCBCR_ENC_XV601:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		ycbcr2rgb(bt601, y, cb, cr, 16, r, g, b);
		break;
	case V4L2_YCBCR_ENC_XV709:
		/* Ignore quantization range, there is only one possible
		 * Y'CbCr encoding. */
		ycbcr2rgb(rec709, y, cb, cr, 16, r, g, b);
		break;
	case V4L2_YCBCR_ENC_BT2020:
		ycbcr2rgb(full ? bt2020_full : bt2020, y, cb, cr, y_offset, r, g, b);
		break;
	case V4L2_YCBCR_ENC_BT2020_CONST_LUM:
		y -= full ? 0 : 16 << 4;
		cb -= 128 << 4;
		cr -= 128 << 4;

		if (cb <= 0)
			*b = y_fac * y + (full ? bt2020c_full[0] : bt2020c[0]) * cb;
		else
			*b = y_fac * y + (full ? bt2020c_full[1] : bt2020c[1]) * cb;
		*b = *b >> 12;
		if (cr <= 0)
			*r = y_fac * y + (full ? bt2020c_full[2] : bt2020c[2]) * cr;
		else
			*r = y_fac * y + (full ? bt2020c_full[3] : bt2020c[3]) * cr;
		*r = *r >> 12;
		lin_r = rec709_to_linear(*r);
		lin_b = rec709_to_linear(*b);
		lin_y = rec709_to_linear((y * 255) / (full ? 255 : 219));

		lin_g = COEFF(1.0 / 0.6780, 255) * lin_y -
			COEFF(0.2627 / 0.6780, 255) * lin_r -
			COEFF(0.0593 / 0.6780, 255) * lin_b;
		*g = linear_to_rec709(lin_g >> 12);
		break;
	case V4L2_YCBCR_ENC_SMPTE240M:
		ycbcr2rgb(full ? smpte240m_full : smpte240m, y, cb, cr, y_offset, r, g, b);
		break;
	case V4L2_YCBCR_ENC_709:
	default:
		ycbcr2rgb(full ? rec709_full : rec709, y, cb, cr, y_offset, r, g, b);
		break;
	}
}