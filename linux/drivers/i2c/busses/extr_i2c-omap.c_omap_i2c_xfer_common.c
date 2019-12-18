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
struct omap_i2c_dev {int latency; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* set_mpu_wkup_lat ) (int /*<<< orphan*/ ,int) ;} ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 struct omap_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int omap_i2c_wait_for_bb (struct omap_i2c_dev*) ; 
 int omap_i2c_wait_for_bb_valid (struct omap_i2c_dev*) ; 
 int omap_i2c_xfer_msg (struct i2c_adapter*,struct i2c_msg*,int,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
omap_i2c_xfer_common(struct i2c_adapter *adap, struct i2c_msg msgs[], int num,
		     bool polling)
{
	struct omap_i2c_dev *omap = i2c_get_adapdata(adap);
	int i;
	int r;

	r = pm_runtime_get_sync(omap->dev);
	if (r < 0)
		goto out;

	r = omap_i2c_wait_for_bb_valid(omap);
	if (r < 0)
		goto out;

	r = omap_i2c_wait_for_bb(omap);
	if (r < 0)
		goto out;

	if (omap->set_mpu_wkup_lat != NULL)
		omap->set_mpu_wkup_lat(omap->dev, omap->latency);

	for (i = 0; i < num; i++) {
		r = omap_i2c_xfer_msg(adap, &msgs[i], (i == (num - 1)),
				      polling);
		if (r != 0)
			break;
	}

	if (r == 0)
		r = num;

	omap_i2c_wait_for_bb(omap);

	if (omap->set_mpu_wkup_lat != NULL)
		omap->set_mpu_wkup_lat(omap->dev, -1);

out:
	pm_runtime_mark_last_busy(omap->dev);
	pm_runtime_put_autosuspend(omap->dev);
	return r;
}