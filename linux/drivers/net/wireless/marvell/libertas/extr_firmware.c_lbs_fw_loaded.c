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
struct lbs_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  fw_waitq; int /*<<< orphan*/  (* fw_callback ) (struct lbs_private*,int,struct firmware const*,struct firmware const*) ;} ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lbs_deb_fw (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct lbs_private*,int,struct firmware const*,struct firmware const*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lbs_fw_loaded(struct lbs_private *priv, int ret,
	const struct firmware *helper, const struct firmware *mainfw)
{
	unsigned long flags;

	lbs_deb_fw("firmware load complete, code %d\n", ret);

	/* User must free helper/mainfw */
	priv->fw_callback(priv, ret, helper, mainfw);

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->fw_callback = NULL;
	wake_up(&priv->fw_waitq);
	spin_unlock_irqrestore(&priv->driver_lock, flags);
}