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
struct mtk_hdmi {int /*<<< orphan*/  cec_dev; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 struct mtk_hdmi* hdmi_ctx_from_conn (struct drm_connector*) ; 
 int /*<<< orphan*/  mtk_cec_set_hpd_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_conn_destroy(struct drm_connector *conn)
{
	struct mtk_hdmi *hdmi = hdmi_ctx_from_conn(conn);

	mtk_cec_set_hpd_event(hdmi->cec_dev, NULL, NULL);

	drm_connector_cleanup(conn);
}