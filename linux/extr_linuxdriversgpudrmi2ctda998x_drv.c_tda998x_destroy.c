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
struct tda998x_priv {scalar_t__ cec_notify; int /*<<< orphan*/  cec; int /*<<< orphan*/  detect_work; int /*<<< orphan*/  edid_delay_timer; TYPE_1__* hdmi; scalar_t__ audio_pdev; int /*<<< orphan*/  bridge; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_FLAGS_2_EDID_BLK_RD ; 
 int /*<<< orphan*/  REG_CEC_RXSHPDINTENA ; 
 int /*<<< orphan*/  REG_INT_FLAGS_2 ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_notifier_put (scalar_t__) ; 
 int /*<<< orphan*/  cec_write (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct tda998x_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct tda998x_priv*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  reg_clear (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tda998x_destroy(struct device *dev)
{
	struct tda998x_priv *priv = dev_get_drvdata(dev);

	drm_bridge_remove(&priv->bridge);

	/* disable all IRQs and free the IRQ handler */
	cec_write(priv, REG_CEC_RXSHPDINTENA, 0);
	reg_clear(priv, REG_INT_FLAGS_2, INT_FLAGS_2_EDID_BLK_RD);

	if (priv->audio_pdev)
		platform_device_unregister(priv->audio_pdev);

	if (priv->hdmi->irq)
		free_irq(priv->hdmi->irq, priv);

	del_timer_sync(&priv->edid_delay_timer);
	cancel_work_sync(&priv->detect_work);

	i2c_unregister_device(priv->cec);

	if (priv->cec_notify)
		cec_notifier_put(priv->cec_notify);
}