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
struct solo_enc_dev {int /*<<< orphan*/  ch; scalar_t__ bw_weight; struct solo_dev* solo_dev; } ;
struct solo_dev {int /*<<< orphan*/  enc_bw_remain; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_CAP_CH_COMP_ENA_E (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLO_CAP_CH_SCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_enc_off(struct solo_enc_dev *solo_enc)
{
	struct solo_dev *solo_dev = solo_enc->solo_dev;

	solo_dev->enc_bw_remain += solo_enc->bw_weight;

	solo_reg_write(solo_dev, SOLO_CAP_CH_SCALE(solo_enc->ch), 0);
	solo_reg_write(solo_dev, SOLO_CAP_CH_COMP_ENA_E(solo_enc->ch), 0);
}