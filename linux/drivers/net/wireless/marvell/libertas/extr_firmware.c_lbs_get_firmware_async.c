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
typedef  int /*<<< orphan*/  u32 ;
struct lbs_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  fw_model; int /*<<< orphan*/ * fw_iter; struct lbs_fw_table const* fw_table; scalar_t__ fw_callback; struct device* fw_device; } ;
struct lbs_fw_table {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ lbs_fw_cb ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  lbs_deb_fw (char*) ; 
 int /*<<< orphan*/  load_next_firmware_from_table (struct lbs_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int lbs_get_firmware_async(struct lbs_private *priv, struct device *device,
			    u32 card_model, const struct lbs_fw_table *fw_table,
			    lbs_fw_cb callback)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->driver_lock, flags);
	if (priv->fw_callback) {
		lbs_deb_fw("firmware load already in progress\n");
		spin_unlock_irqrestore(&priv->driver_lock, flags);
		return -EBUSY;
	}

	priv->fw_device = device;
	priv->fw_callback = callback;
	priv->fw_table = fw_table;
	priv->fw_iter = NULL;
	priv->fw_model = card_model;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbs_deb_fw("Starting async firmware load\n");
	load_next_firmware_from_table(priv);
	return 0;
}