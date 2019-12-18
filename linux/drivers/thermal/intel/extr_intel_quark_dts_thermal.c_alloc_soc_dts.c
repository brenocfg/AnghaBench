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
typedef  int u32 ;
struct soc_sensor_entry {int locked; int store_dts_enable; int store_ptps; int /*<<< orphan*/  tzone; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct soc_sensor_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int QRK_DTS_LOCK_BIT ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_ENABLE ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_LOCK ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_PTPS ; 
 int QRK_DTS_WR_MASK_CLR ; 
 int QRK_DTS_WR_MASK_SET ; 
 int /*<<< orphan*/  QRK_MAX_DTS_TRIPS ; 
 int /*<<< orphan*/  QRK_MBI_UNIT_RMU ; 
 int /*<<< orphan*/  dts_update_mutex ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (struct soc_sensor_entry*) ; 
 struct soc_sensor_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  polling_delay ; 
 int soc_dts_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_register (char*,int /*<<< orphan*/ ,int,struct soc_sensor_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tzone_ops ; 

__attribute__((used)) static struct soc_sensor_entry *alloc_soc_dts(void)
{
	struct soc_sensor_entry *aux_entry;
	int err;
	u32 out;
	int wr_mask;

	aux_entry = kzalloc(sizeof(*aux_entry), GFP_KERNEL);
	if (!aux_entry) {
		err = -ENOMEM;
		return ERR_PTR(-ENOMEM);
	}

	/* Check if DTS register is locked */
	err = iosf_mbi_read(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_LOCK, &out);
	if (err)
		goto err_ret;

	if (out & QRK_DTS_LOCK_BIT) {
		aux_entry->locked = true;
		wr_mask = QRK_DTS_WR_MASK_CLR;
	} else {
		aux_entry->locked = false;
		wr_mask = QRK_DTS_WR_MASK_SET;
	}

	/* Store DTS default state if DTS registers are not locked */
	if (!aux_entry->locked) {
		/* Store DTS default enable for restore on exit */
		err = iosf_mbi_read(QRK_MBI_UNIT_RMU, MBI_REG_READ,
				    QRK_DTS_REG_OFFSET_ENABLE,
				    &aux_entry->store_dts_enable);
		if (err)
			goto err_ret;

		/* Store DTS default PTPS register for restore on exit */
		err = iosf_mbi_read(QRK_MBI_UNIT_RMU, MBI_REG_READ,
				    QRK_DTS_REG_OFFSET_PTPS,
				    &aux_entry->store_ptps);
		if (err)
			goto err_ret;
	}

	aux_entry->tzone = thermal_zone_device_register("quark_dts",
			QRK_MAX_DTS_TRIPS,
			wr_mask,
			aux_entry, &tzone_ops, NULL, 0, polling_delay);
	if (IS_ERR(aux_entry->tzone)) {
		err = PTR_ERR(aux_entry->tzone);
		goto err_ret;
	}

	mutex_lock(&dts_update_mutex);
	err = soc_dts_enable(aux_entry->tzone);
	mutex_unlock(&dts_update_mutex);
	if (err)
		goto err_aux_status;

	return aux_entry;

err_aux_status:
	thermal_zone_device_unregister(aux_entry->tzone);
err_ret:
	kfree(aux_entry);
	return ERR_PTR(err);
}