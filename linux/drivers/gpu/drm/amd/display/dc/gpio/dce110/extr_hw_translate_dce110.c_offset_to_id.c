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
typedef  int uint32_t ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
#define  DC_GPIO_GENERIC_A__DC_GPIO_GENERICA_A_MASK 162 
#define  DC_GPIO_GENERIC_A__DC_GPIO_GENERICB_A_MASK 161 
#define  DC_GPIO_GENERIC_A__DC_GPIO_GENERICC_A_MASK 160 
#define  DC_GPIO_GENERIC_A__DC_GPIO_GENERICD_A_MASK 159 
#define  DC_GPIO_GENERIC_A__DC_GPIO_GENERICE_A_MASK 158 
#define  DC_GPIO_GENERIC_A__DC_GPIO_GENERICF_A_MASK 157 
#define  DC_GPIO_GENERIC_A__DC_GPIO_GENERICG_A_MASK 156 
#define  DC_GPIO_GENLK_A__DC_GPIO_GENLK_CLK_A_MASK 155 
#define  DC_GPIO_GENLK_A__DC_GPIO_GENLK_VSYNC_A_MASK 154 
#define  DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_A_A_MASK 153 
#define  DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_B_A_MASK 152 
#define  DC_GPIO_HPD_A__DC_GPIO_HPD1_A_MASK 151 
#define  DC_GPIO_HPD_A__DC_GPIO_HPD2_A_MASK 150 
#define  DC_GPIO_HPD_A__DC_GPIO_HPD3_A_MASK 149 
#define  DC_GPIO_HPD_A__DC_GPIO_HPD4_A_MASK 148 
#define  DC_GPIO_HPD_A__DC_GPIO_HPD5_A_MASK 147 
#define  DC_GPIO_HPD_A__DC_GPIO_HPD6_A_MASK 146 
#define  DC_GPIO_SYNCA_A__DC_GPIO_HSYNCA_A_MASK 145 
#define  DC_GPIO_SYNCA_A__DC_GPIO_VSYNCA_A_MASK 144 
 int GPIO_DDC_LINE_DDC1 ; 
 int GPIO_DDC_LINE_DDC2 ; 
 int GPIO_DDC_LINE_DDC3 ; 
 int GPIO_DDC_LINE_DDC4 ; 
 int GPIO_DDC_LINE_DDC5 ; 
 int GPIO_DDC_LINE_DDC6 ; 
 int GPIO_DDC_LINE_DDC_VGA ; 
 int GPIO_DDC_LINE_I2C_PAD ; 
 int GPIO_GENERIC_A ; 
 int GPIO_GENERIC_B ; 
 int GPIO_GENERIC_C ; 
 int GPIO_GENERIC_D ; 
 int GPIO_GENERIC_E ; 
 int GPIO_GENERIC_F ; 
 int GPIO_GENERIC_G ; 
 int GPIO_GSL_GENLOCK_CLOCK ; 
 int GPIO_GSL_GENLOCK_VSYNC ; 
 int GPIO_GSL_SWAPLOCK_A ; 
 int GPIO_GSL_SWAPLOCK_B ; 
 int GPIO_HPD_1 ; 
 int GPIO_HPD_2 ; 
 int GPIO_HPD_3 ; 
 int GPIO_HPD_4 ; 
 int GPIO_HPD_5 ; 
 int GPIO_HPD_6 ; 
 int GPIO_ID_GENERIC ; 
 int GPIO_ID_GSL ; 
 int GPIO_ID_HPD ; 
 int GPIO_ID_SYNC ; 
 int GPIO_SYNC_HSYNC_A ; 
 int GPIO_SYNC_VSYNC_A ; 
#define  mmDC_GPIO_DDC1_A 143 
#define  mmDC_GPIO_DDC2_A 142 
#define  mmDC_GPIO_DDC3_A 141 
#define  mmDC_GPIO_DDC4_A 140 
#define  mmDC_GPIO_DDC5_A 139 
#define  mmDC_GPIO_DDC6_A 138 
#define  mmDC_GPIO_DDCVGA_A 137 
#define  mmDC_GPIO_DEBUG 136 
#define  mmDC_GPIO_GENERIC_A 135 
#define  mmDC_GPIO_GENLK_A 134 
#define  mmDC_GPIO_HPD_A 133 
#define  mmDC_GPIO_I2CPAD_A 132 
#define  mmDC_GPIO_PAD_STRENGTH_1 131 
#define  mmDC_GPIO_PAD_STRENGTH_2 130 
#define  mmDC_GPIO_PWRSEQ_A 129 
#define  mmDC_GPIO_SYNCA_A 128 

__attribute__((used)) static bool offset_to_id(
	uint32_t offset,
	uint32_t mask,
	enum gpio_id *id,
	uint32_t *en)
{
	switch (offset) {
	/* GENERIC */
	case mmDC_GPIO_GENERIC_A:
		*id = GPIO_ID_GENERIC;
		switch (mask) {
		case DC_GPIO_GENERIC_A__DC_GPIO_GENERICA_A_MASK:
			*en = GPIO_GENERIC_A;
			return true;
		case DC_GPIO_GENERIC_A__DC_GPIO_GENERICB_A_MASK:
			*en = GPIO_GENERIC_B;
			return true;
		case DC_GPIO_GENERIC_A__DC_GPIO_GENERICC_A_MASK:
			*en = GPIO_GENERIC_C;
			return true;
		case DC_GPIO_GENERIC_A__DC_GPIO_GENERICD_A_MASK:
			*en = GPIO_GENERIC_D;
			return true;
		case DC_GPIO_GENERIC_A__DC_GPIO_GENERICE_A_MASK:
			*en = GPIO_GENERIC_E;
			return true;
		case DC_GPIO_GENERIC_A__DC_GPIO_GENERICF_A_MASK:
			*en = GPIO_GENERIC_F;
			return true;
		case DC_GPIO_GENERIC_A__DC_GPIO_GENERICG_A_MASK:
			*en = GPIO_GENERIC_G;
			return true;
		default:
			ASSERT_CRITICAL(false);
			return false;
		}
	break;
	/* HPD */
	case mmDC_GPIO_HPD_A:
		*id = GPIO_ID_HPD;
		switch (mask) {
		case DC_GPIO_HPD_A__DC_GPIO_HPD1_A_MASK:
			*en = GPIO_HPD_1;
			return true;
		case DC_GPIO_HPD_A__DC_GPIO_HPD2_A_MASK:
			*en = GPIO_HPD_2;
			return true;
		case DC_GPIO_HPD_A__DC_GPIO_HPD3_A_MASK:
			*en = GPIO_HPD_3;
			return true;
		case DC_GPIO_HPD_A__DC_GPIO_HPD4_A_MASK:
			*en = GPIO_HPD_4;
			return true;
		case DC_GPIO_HPD_A__DC_GPIO_HPD5_A_MASK:
			*en = GPIO_HPD_5;
			return true;
		case DC_GPIO_HPD_A__DC_GPIO_HPD6_A_MASK:
			*en = GPIO_HPD_6;
			return true;
		default:
			ASSERT_CRITICAL(false);
			return false;
		}
	break;
	/* SYNCA */
	case mmDC_GPIO_SYNCA_A:
		*id = GPIO_ID_SYNC;
		switch (mask) {
		case DC_GPIO_SYNCA_A__DC_GPIO_HSYNCA_A_MASK:
			*en = GPIO_SYNC_HSYNC_A;
			return true;
		case DC_GPIO_SYNCA_A__DC_GPIO_VSYNCA_A_MASK:
			*en = GPIO_SYNC_VSYNC_A;
			return true;
		default:
			ASSERT_CRITICAL(false);
			return false;
		}
	break;
	/* mmDC_GPIO_GENLK_MASK */
	case mmDC_GPIO_GENLK_A:
		*id = GPIO_ID_GSL;
		switch (mask) {
		case DC_GPIO_GENLK_A__DC_GPIO_GENLK_CLK_A_MASK:
			*en = GPIO_GSL_GENLOCK_CLOCK;
			return true;
		case DC_GPIO_GENLK_A__DC_GPIO_GENLK_VSYNC_A_MASK:
			*en = GPIO_GSL_GENLOCK_VSYNC;
			return true;
		case DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_A_A_MASK:
			*en = GPIO_GSL_SWAPLOCK_A;
			return true;
		case DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_B_A_MASK:
			*en = GPIO_GSL_SWAPLOCK_B;
			return true;
		default:
			ASSERT_CRITICAL(false);
			return false;
		}
	break;
	/* DDC */
	/* we don't care about the GPIO_ID for DDC
	 * in DdcHandle it will use GPIO_ID_DDC_DATA/GPIO_ID_DDC_CLOCK
	 * directly in the create method */
	case mmDC_GPIO_DDC1_A:
		*en = GPIO_DDC_LINE_DDC1;
		return true;
	case mmDC_GPIO_DDC2_A:
		*en = GPIO_DDC_LINE_DDC2;
		return true;
	case mmDC_GPIO_DDC3_A:
		*en = GPIO_DDC_LINE_DDC3;
		return true;
	case mmDC_GPIO_DDC4_A:
		*en = GPIO_DDC_LINE_DDC4;
		return true;
	case mmDC_GPIO_DDC5_A:
		*en = GPIO_DDC_LINE_DDC5;
		return true;
	case mmDC_GPIO_DDC6_A:
		*en = GPIO_DDC_LINE_DDC6;
		return true;
	case mmDC_GPIO_DDCVGA_A:
		*en = GPIO_DDC_LINE_DDC_VGA;
		return true;
	/* GPIO_I2CPAD */
	case mmDC_GPIO_I2CPAD_A:
		*en = GPIO_DDC_LINE_I2C_PAD;
		return true;
	/* Not implemented */
	case mmDC_GPIO_PWRSEQ_A:
	case mmDC_GPIO_PAD_STRENGTH_1:
	case mmDC_GPIO_PAD_STRENGTH_2:
	case mmDC_GPIO_DEBUG:
		return false;
	/* UNEXPECTED */
	default:
		ASSERT_CRITICAL(false);
		return false;
	}
}