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
typedef  int u8 ;
struct solo_enc_dev {int ch; scalar_t__ bw_weight; scalar_t__ type; int interval; int gop; int qp; int mode; scalar_t__ interlaced; scalar_t__ sequence; struct solo_dev* solo_dev; } ;
struct solo_dev {scalar_t__ enc_bw_remain; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SOLO_CAP_CH_COMP_ENA_E (int) ; 
 int /*<<< orphan*/  SOLO_CAP_CH_INTV (int) ; 
 int /*<<< orphan*/  SOLO_CAP_CH_INTV_E (int) ; 
 int /*<<< orphan*/  SOLO_CAP_CH_SCALE (int) ; 
 scalar_t__ SOLO_ENC_TYPE_EXT ; 
 int /*<<< orphan*/  SOLO_VE_CH_GOP (int) ; 
 int /*<<< orphan*/  SOLO_VE_CH_GOP_E (int) ; 
 int /*<<< orphan*/  SOLO_VE_CH_INTL (int) ; 
 int /*<<< orphan*/  SOLO_VE_CH_QP (int) ; 
 int /*<<< orphan*/  SOLO_VE_CH_QP_E (int) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  solo_update_mode (struct solo_enc_dev*) ; 

__attribute__((used)) static int solo_enc_on(struct solo_enc_dev *solo_enc)
{
	u8 ch = solo_enc->ch;
	struct solo_dev *solo_dev = solo_enc->solo_dev;
	u8 interval;

	solo_update_mode(solo_enc);

	/* Make sure to do a bandwidth check */
	if (solo_enc->bw_weight > solo_dev->enc_bw_remain)
		return -EBUSY;
	solo_enc->sequence = 0;
	solo_dev->enc_bw_remain -= solo_enc->bw_weight;

	if (solo_enc->type == SOLO_ENC_TYPE_EXT)
		solo_reg_write(solo_dev, SOLO_CAP_CH_COMP_ENA_E(ch), 1);

	/* Disable all encoding for this channel */
	solo_reg_write(solo_dev, SOLO_CAP_CH_SCALE(ch), 0);

	/* Common for both std and ext encoding */
	solo_reg_write(solo_dev, SOLO_VE_CH_INTL(ch),
		       solo_enc->interlaced ? 1 : 0);

	if (solo_enc->interlaced)
		interval = solo_enc->interval - 1;
	else
		interval = solo_enc->interval;

	/* Standard encoding only */
	solo_reg_write(solo_dev, SOLO_VE_CH_GOP(ch), solo_enc->gop);
	solo_reg_write(solo_dev, SOLO_VE_CH_QP(ch), solo_enc->qp);
	solo_reg_write(solo_dev, SOLO_CAP_CH_INTV(ch), interval);

	/* Extended encoding only */
	solo_reg_write(solo_dev, SOLO_VE_CH_GOP_E(ch), solo_enc->gop);
	solo_reg_write(solo_dev, SOLO_VE_CH_QP_E(ch), solo_enc->qp);
	solo_reg_write(solo_dev, SOLO_CAP_CH_INTV_E(ch), interval);

	/* Enables the standard encoder */
	solo_reg_write(solo_dev, SOLO_CAP_CH_SCALE(ch), solo_enc->mode);

	return 0;
}