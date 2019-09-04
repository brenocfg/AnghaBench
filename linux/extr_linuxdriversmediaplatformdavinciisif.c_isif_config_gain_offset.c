#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_14__ {int integer; int decimal; } ;
struct TYPE_13__ {int integer; int decimal; } ;
struct TYPE_12__ {int integer; int decimal; } ;
struct TYPE_11__ {int integer; int decimal; } ;
struct TYPE_15__ {TYPE_6__ b_mg; TYPE_5__ gb_g; TYPE_4__ gr_cy; TYPE_3__ r_ye; } ;
struct isif_gain_offsets_adj {int offset; TYPE_7__ gain; int /*<<< orphan*/  offset_h3a_en; int /*<<< orphan*/  offset_ipipe_en; int /*<<< orphan*/  offset_sdram_en; int /*<<< orphan*/  gain_h3a_en; int /*<<< orphan*/  gain_ipipe_en; int /*<<< orphan*/  gain_sdram_en; } ;
struct TYPE_9__ {struct isif_gain_offsets_adj gain_offset; } ;
struct TYPE_10__ {TYPE_1__ config_params; } ;
struct TYPE_16__ {TYPE_2__ bayer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBGAIN ; 
 int /*<<< orphan*/  CGAMMAWD ; 
 int /*<<< orphan*/  CGBGAIN ; 
 int /*<<< orphan*/  CGRGAIN ; 
 int /*<<< orphan*/  COFSTA ; 
 int /*<<< orphan*/  CRGAIN ; 
 int GAIN_H3A_EN_SHIFT ; 
 int GAIN_INTEGER_SHIFT ; 
 int GAIN_IPIPE_EN_SHIFT ; 
 int /*<<< orphan*/  GAIN_OFFSET_EN_MASK ; 
 int GAIN_SDRAM_EN_SHIFT ; 
 int OFST_H3A_EN_SHIFT ; 
 int OFST_IPIPE_EN_SHIFT ; 
 int OFST_SDRAM_EN_SHIFT ; 
 TYPE_8__ isif_cfg ; 
 int /*<<< orphan*/  reg_modify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_config_gain_offset(void)
{
	struct isif_gain_offsets_adj *gain_off_p =
		&isif_cfg.bayer.config_params.gain_offset;
	u32 val;

	val = (!!gain_off_p->gain_sdram_en << GAIN_SDRAM_EN_SHIFT) |
	      (!!gain_off_p->gain_ipipe_en << GAIN_IPIPE_EN_SHIFT) |
	      (!!gain_off_p->gain_h3a_en << GAIN_H3A_EN_SHIFT) |
	      (!!gain_off_p->offset_sdram_en << OFST_SDRAM_EN_SHIFT) |
	      (!!gain_off_p->offset_ipipe_en << OFST_IPIPE_EN_SHIFT) |
	      (!!gain_off_p->offset_h3a_en << OFST_H3A_EN_SHIFT);

	reg_modify(GAIN_OFFSET_EN_MASK, val, CGAMMAWD);

	val = (gain_off_p->gain.r_ye.integer << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.r_ye.decimal;
	regw(val, CRGAIN);

	val = (gain_off_p->gain.gr_cy.integer << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.gr_cy.decimal;
	regw(val, CGRGAIN);

	val = (gain_off_p->gain.gb_g.integer << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.gb_g.decimal;
	regw(val, CGBGAIN);

	val = (gain_off_p->gain.b_mg.integer << GAIN_INTEGER_SHIFT) |
	       gain_off_p->gain.b_mg.decimal;
	regw(val, CBGAIN);

	regw(gain_off_p->offset, COFSTA);
}