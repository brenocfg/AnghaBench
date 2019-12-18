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
struct ath_hw_antcomb_conf {int div_group; int main_lna_conf; int alt_lna_conf; int fast_div_bias; scalar_t__ alt_gaintb; scalar_t__ main_gaintb; } ;
struct ath_ant_comb {int ant_ratio; int fast_div_bias; int /*<<< orphan*/  scan; } ;

/* Variables and functions */
 int ATH_ANT_DIV_COMB_ALT_ANT_RATIO ; 

__attribute__((used)) static void ath_ant_div_conf_fast_divbias(struct ath_hw_antcomb_conf *ant_conf,
					  struct ath_ant_comb *antcomb,
					  int alt_ratio)
{
	ant_conf->main_gaintb = 0;
	ant_conf->alt_gaintb = 0;

	if (ant_conf->div_group == 0) {
		/* Adjust the fast_div_bias based on main and alt lna conf */
		switch ((ant_conf->main_lna_conf << 4) |
				ant_conf->alt_lna_conf) {
		case 0x01: /* A-B LNA2 */
			ant_conf->fast_div_bias = 0x3b;
			break;
		case 0x02: /* A-B LNA1 */
			ant_conf->fast_div_bias = 0x3d;
			break;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x10: /* LNA2 A-B */
			ant_conf->fast_div_bias = 0x7;
			break;
		case 0x12: /* LNA2 LNA1 */
			ant_conf->fast_div_bias = 0x2;
			break;
		case 0x13: /* LNA2 A+B */
			ant_conf->fast_div_bias = 0x7;
			break;
		case 0x20: /* LNA1 A-B */
			ant_conf->fast_div_bias = 0x6;
			break;
		case 0x21: /* LNA1 LNA2 */
			ant_conf->fast_div_bias = 0x0;
			break;
		case 0x23: /* LNA1 A+B */
			ant_conf->fast_div_bias = 0x6;
			break;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x31: /* A+B LNA2 */
			ant_conf->fast_div_bias = 0x3b;
			break;
		case 0x32: /* A+B LNA1 */
			ant_conf->fast_div_bias = 0x3d;
			break;
		default:
			break;
		}
	} else if (ant_conf->div_group == 1) {
		/* Adjust the fast_div_bias based on main and alt_lna_conf */
		switch ((ant_conf->main_lna_conf << 4) |
			ant_conf->alt_lna_conf) {
		case 0x01: /* A-B LNA2 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x02: /* A-B LNA1 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x10: /* LNA2 A-B */
			if (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_div_bias = 0x3f;
			else
				ant_conf->fast_div_bias = 0x1;
			break;
		case 0x12: /* LNA2 LNA1 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x13: /* LNA2 A+B */
			if (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_div_bias = 0x3f;
			else
				ant_conf->fast_div_bias = 0x1;
			break;
		case 0x20: /* LNA1 A-B */
			if (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_div_bias = 0x3f;
			else
				ant_conf->fast_div_bias = 0x1;
			break;
		case 0x21: /* LNA1 LNA2 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x23: /* LNA1 A+B */
			if (!(antcomb->scan) &&
			    (alt_ratio > ATH_ANT_DIV_COMB_ALT_ANT_RATIO))
				ant_conf->fast_div_bias = 0x3f;
			else
				ant_conf->fast_div_bias = 0x1;
			break;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x31: /* A+B LNA2 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x32: /* A+B LNA1 */
			ant_conf->fast_div_bias = 0x1;
			break;
		default:
			break;
		}
	} else if (ant_conf->div_group == 2) {
		/* Adjust the fast_div_bias based on main and alt_lna_conf */
		switch ((ant_conf->main_lna_conf << 4) |
				ant_conf->alt_lna_conf) {
		case 0x01: /* A-B LNA2 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x02: /* A-B LNA1 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x10: /* LNA2 A-B */
			if (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_div_bias = 0x1;
			else
				ant_conf->fast_div_bias = 0x2;
			break;
		case 0x12: /* LNA2 LNA1 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x13: /* LNA2 A+B */
			if (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_div_bias = 0x1;
			else
				ant_conf->fast_div_bias = 0x2;
			break;
		case 0x20: /* LNA1 A-B */
			if (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_div_bias = 0x1;
			else
				ant_conf->fast_div_bias = 0x2;
			break;
		case 0x21: /* LNA1 LNA2 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x23: /* LNA1 A+B */
			if (!antcomb->scan && (alt_ratio > antcomb->ant_ratio))
				ant_conf->fast_div_bias = 0x1;
			else
				ant_conf->fast_div_bias = 0x2;
			break;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x31: /* A+B LNA2 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x32: /* A+B LNA1 */
			ant_conf->fast_div_bias = 0x1;
			break;
		default:
			break;
		}

		if (antcomb->fast_div_bias)
			ant_conf->fast_div_bias = antcomb->fast_div_bias;
	} else if (ant_conf->div_group == 3) {
		switch ((ant_conf->main_lna_conf << 4) |
			ant_conf->alt_lna_conf) {
		case 0x01: /* A-B LNA2 */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x02: /* A-B LNA1 */
			ant_conf->fast_div_bias = 0x39;
			break;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x10: /* LNA2 A-B */
			ant_conf->fast_div_bias = 0x2;
			break;
		case 0x12: /* LNA2 LNA1 */
			ant_conf->fast_div_bias = 0x3f;
			break;
		case 0x13: /* LNA2 A+B */
			ant_conf->fast_div_bias = 0x2;
			break;
		case 0x20: /* LNA1 A-B */
			ant_conf->fast_div_bias = 0x3;
			break;
		case 0x21: /* LNA1 LNA2 */
			ant_conf->fast_div_bias = 0x3;
			break;
		case 0x23: /* LNA1 A+B */
			ant_conf->fast_div_bias = 0x3;
			break;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			break;
		case 0x31: /* A+B LNA2 */
			ant_conf->fast_div_bias = 0x6;
			break;
		case 0x32: /* A+B LNA1 */
			ant_conf->fast_div_bias = 0x1;
			break;
		default:
			break;
		}
	}
}