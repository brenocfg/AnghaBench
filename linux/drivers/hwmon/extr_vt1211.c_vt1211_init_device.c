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
struct vt1211_data {int uch_config; int** pwm_auto_pwm; int /*<<< orphan*/  vrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT1211_REG_TEMP1_CONFIG ; 
 int /*<<< orphan*/  VT1211_REG_TEMP2_CONFIG ; 
 int /*<<< orphan*/  VT1211_REG_UCH_CONFIG ; 
 scalar_t__ int_mode ; 
 int uch_config ; 
 int /*<<< orphan*/  vid_which_vrm () ; 
 int vt1211_read8 (struct vt1211_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt1211_write8 (struct vt1211_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vt1211_init_device(struct vt1211_data *data)
{
	/* set VRM */
	data->vrm = vid_which_vrm();

	/* Read (and initialize) UCH config */
	data->uch_config = vt1211_read8(data, VT1211_REG_UCH_CONFIG);
	if (uch_config > -1) {
		data->uch_config = (data->uch_config & 0x83) |
				   (uch_config << 2);
		vt1211_write8(data, VT1211_REG_UCH_CONFIG, data->uch_config);
	}

	/*
	 * Initialize the interrupt mode (if request at module load time).
	 * The VT1211 implements 3 different modes for clearing interrupts:
	 * 0: Clear INT when status register is read. Regenerate INT as long
	 *    as temp stays above hysteresis limit.
	 * 1: Clear INT when status register is read. DON'T regenerate INT
	 *    until temp falls below hysteresis limit and exceeds hot limit
	 *    again.
	 * 2: Clear INT when temp falls below max limit.
	 *
	 * The driver only allows to force mode 0 since that's the only one
	 * that makes sense for 'sensors'
	 */
	if (int_mode == 0) {
		vt1211_write8(data, VT1211_REG_TEMP1_CONFIG, 0);
		vt1211_write8(data, VT1211_REG_TEMP2_CONFIG, 0);
	}

	/* Fill in some hard wired values into our data struct */
	data->pwm_auto_pwm[0][3] = 255;
	data->pwm_auto_pwm[1][3] = 255;
}