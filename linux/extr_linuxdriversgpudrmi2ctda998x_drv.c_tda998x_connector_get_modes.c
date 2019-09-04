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
struct tda998x_priv {scalar_t__ rev; int /*<<< orphan*/  audio_mutex; int /*<<< orphan*/  sink_has_audio; int /*<<< orphan*/  cec_notify; TYPE_1__* hdmi; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TX4 ; 
 scalar_t__ TDA19988 ; 
 int /*<<< orphan*/  TX4_PD_RAM ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr_from_edid (int /*<<< orphan*/ ,struct edid*) ; 
 struct tda998x_priv* conn_to_tda998x_priv (struct drm_connector*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_detect_monitor_audio (struct edid*) ; 
 struct edid* drm_do_get_edid (struct drm_connector*,int /*<<< orphan*/ ,struct tda998x_priv*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_edid_block ; 
 int /*<<< orphan*/  reg_clear (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_set (struct tda998x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tda998x_edid_delay_wait (struct tda998x_priv*) ; 

__attribute__((used)) static int tda998x_connector_get_modes(struct drm_connector *connector)
{
	struct tda998x_priv *priv = conn_to_tda998x_priv(connector);
	struct edid *edid;
	int n;

	/*
	 * If we get killed while waiting for the HPD timeout, return
	 * no modes found: we are not in a restartable path, so we
	 * can't handle signals gracefully.
	 */
	if (tda998x_edid_delay_wait(priv))
		return 0;

	if (priv->rev == TDA19988)
		reg_clear(priv, REG_TX4, TX4_PD_RAM);

	edid = drm_do_get_edid(connector, read_edid_block, priv);

	if (priv->rev == TDA19988)
		reg_set(priv, REG_TX4, TX4_PD_RAM);

	if (!edid) {
		dev_warn(&priv->hdmi->dev, "failed to read EDID\n");
		return 0;
	}

	drm_connector_update_edid_property(connector, edid);
	cec_notifier_set_phys_addr_from_edid(priv->cec_notify, edid);

	mutex_lock(&priv->audio_mutex);
	n = drm_add_edid_modes(connector, edid);
	priv->sink_has_audio = drm_detect_monitor_audio(edid);
	mutex_unlock(&priv->audio_mutex);

	kfree(edid);

	return n;
}