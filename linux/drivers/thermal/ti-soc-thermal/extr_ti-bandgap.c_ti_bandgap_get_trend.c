#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ti_bandgap {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_2__* conf; } ;
struct temp_sensor_registers {int /*<<< orphan*/  bgap_dtemp_mask; int /*<<< orphan*/  ctrl_dtemp_2; int /*<<< orphan*/  ctrl_dtemp_1; } ;
struct TYPE_4__ {TYPE_1__* sensors; } ;
struct TYPE_3__ {struct temp_sensor_registers* registers; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  FREEZE_BIT ; 
 int /*<<< orphan*/  HISTORY_BUFFER ; 
 int /*<<< orphan*/  RMW_BITS (struct ti_bandgap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TI_BANDGAP_HAS (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgap_mask_ctrl ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  mask_freeze_mask ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ti_bandgap_adc_to_mcelsius (struct ti_bandgap*,int /*<<< orphan*/ ,int*) ; 
 int ti_bandgap_read_update_interval (struct ti_bandgap*,int,int*) ; 
 int /*<<< orphan*/  ti_bandgap_readl (struct ti_bandgap*,int /*<<< orphan*/ ) ; 
 int ti_bandgap_validate (struct ti_bandgap*,int) ; 

int ti_bandgap_get_trend(struct ti_bandgap *bgp, int id, int *trend)
{
	struct temp_sensor_registers *tsr;
	u32 temp1, temp2, reg1, reg2;
	int t1, t2, interval, ret = 0;

	ret = ti_bandgap_validate(bgp, id);
	if (ret)
		goto exit;

	if (!TI_BANDGAP_HAS(bgp, HISTORY_BUFFER) ||
	    !TI_BANDGAP_HAS(bgp, FREEZE_BIT)) {
		ret = -ENOTSUPP;
		goto exit;
	}

	spin_lock(&bgp->lock);

	tsr = bgp->conf->sensors[id].registers;

	/* Freeze and read the last 2 valid readings */
	RMW_BITS(bgp, id, bgap_mask_ctrl, mask_freeze_mask, 1);
	reg1 = tsr->ctrl_dtemp_1;
	reg2 = tsr->ctrl_dtemp_2;

	/* read temperature from history buffer */
	temp1 = ti_bandgap_readl(bgp, reg1);
	temp1 &= tsr->bgap_dtemp_mask;

	temp2 = ti_bandgap_readl(bgp, reg2);
	temp2 &= tsr->bgap_dtemp_mask;

	/* Convert from adc values to mCelsius temperature */
	ret = ti_bandgap_adc_to_mcelsius(bgp, temp1, &t1);
	if (ret)
		goto unfreeze;

	ret = ti_bandgap_adc_to_mcelsius(bgp, temp2, &t2);
	if (ret)
		goto unfreeze;

	/* Fetch the update interval */
	ret = ti_bandgap_read_update_interval(bgp, id, &interval);
	if (ret)
		goto unfreeze;

	/* Set the interval to 1 ms if bandgap counter delay is not set */
	if (interval == 0)
		interval = 1;

	*trend = (t1 - t2) / interval;

	dev_dbg(bgp->dev, "The temperatures are t1 = %d and t2 = %d and trend =%d\n",
		t1, t2, *trend);

unfreeze:
	RMW_BITS(bgp, id, bgap_mask_ctrl, mask_freeze_mask, 0);
	spin_unlock(&bgp->lock);
exit:
	return ret;
}