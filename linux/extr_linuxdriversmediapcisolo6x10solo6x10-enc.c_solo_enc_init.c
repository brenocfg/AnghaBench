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
struct solo_dev {int nr_chans; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_CAP_CH_COMP_ENA_E (int) ; 
 int /*<<< orphan*/  SOLO_CAP_CH_SCALE (int) ; 
 int /*<<< orphan*/  solo_capture_config (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_jpeg_config (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_mp4e_config (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int solo_enc_init(struct solo_dev *solo_dev)
{
	int i;

	solo_capture_config(solo_dev);
	solo_mp4e_config(solo_dev);
	solo_jpeg_config(solo_dev);

	for (i = 0; i < solo_dev->nr_chans; i++) {
		solo_reg_write(solo_dev, SOLO_CAP_CH_SCALE(i), 0);
		solo_reg_write(solo_dev, SOLO_CAP_CH_COMP_ENA_E(i), 0);
	}

	return 0;
}