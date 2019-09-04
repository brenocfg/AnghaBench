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
typedef  enum tgp_color_enc { ____Placeholder_tgp_color_enc } tgp_color_enc ;

/* Variables and functions */
#define  TGP_COLOR_ENC_HSV 131 
#define  TGP_COLOR_ENC_LUMA 130 
#define  TGP_COLOR_ENC_RGB 129 
#define  TGP_COLOR_ENC_YCBCR 128 

__attribute__((used)) static const char *tpg_color_enc_str(enum tgp_color_enc
						 color_enc)
{
	switch (color_enc) {
	case TGP_COLOR_ENC_HSV:
		return "HSV";
	case TGP_COLOR_ENC_YCBCR:
		return "Y'CbCr";
	case TGP_COLOR_ENC_LUMA:
		return "Luma";
	case TGP_COLOR_ENC_RGB:
	default:
		return "R'G'B";

	}
}