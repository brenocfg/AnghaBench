#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct saa7146_vv {int current_hps_source; int current_hps_sync; int /*<<< orphan*/  hflip; TYPE_1__* standard; } ;
struct saa7146_dev {struct saa7146_vv* vv_data; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_2__ {int v_field; int /*<<< orphan*/  h_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPS_CTRL ; 
 int /*<<< orphan*/  HPS_H_PRESCALE ; 
 int /*<<< orphan*/  HPS_H_SCALE ; 
 int /*<<< orphan*/  HPS_V_GAIN ; 
 int /*<<< orphan*/  HPS_V_SCALE ; 
 int MASK_05 ; 
 int MASK_06 ; 
 int MASK_21 ; 
 int MASK_22 ; 
 int /*<<< orphan*/  MC2 ; 
 int /*<<< orphan*/  calculate_h_scale_registers (struct saa7146_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  calculate_hps_source_and_sync (struct saa7146_dev*,int,int,int*) ; 
 int /*<<< orphan*/  calculate_hxo_and_hyo (struct saa7146_vv*,int*,int*) ; 
 int /*<<< orphan*/  calculate_v_scale_registers (struct saa7146_dev*,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void saa7146_set_window(struct saa7146_dev *dev, int width, int height, enum v4l2_field field)
{
	struct saa7146_vv *vv = dev->vv_data;

	int source = vv->current_hps_source;
	int sync = vv->current_hps_sync;

	u32 hps_v_scale = 0, hps_v_gain  = 0, hps_ctrl = 0, hps_h_prescale = 0, hps_h_scale = 0;

	/* set vertical scale */
	hps_v_scale = 0; /* all bits get set by the function-call */
	hps_v_gain  = 0; /* fixme: saa7146_read(dev, HPS_V_GAIN);*/
	calculate_v_scale_registers(dev, field, vv->standard->v_field*2, height, &hps_v_scale, &hps_v_gain);

	/* set horizontal scale */
	hps_ctrl	= 0;
	hps_h_prescale	= 0; /* all bits get set in the function */
	hps_h_scale	= 0;
	calculate_h_scale_registers(dev, vv->standard->h_pixels, width, vv->hflip, &hps_ctrl, &hps_v_gain, &hps_h_prescale, &hps_h_scale);

	/* set hyo and hxo */
	calculate_hxo_and_hyo(vv, &hps_h_scale, &hps_ctrl);
	calculate_hps_source_and_sync(dev, source, sync, &hps_ctrl);

	/* write out new register contents */
	saa7146_write(dev, HPS_V_SCALE,	hps_v_scale);
	saa7146_write(dev, HPS_V_GAIN,	hps_v_gain);
	saa7146_write(dev, HPS_CTRL,	hps_ctrl);
	saa7146_write(dev, HPS_H_PRESCALE,hps_h_prescale);
	saa7146_write(dev, HPS_H_SCALE,	hps_h_scale);

	/* upload shadow-ram registers */
	saa7146_write(dev, MC2, (MASK_05 | MASK_06 | MASK_21 | MASK_22) );
}