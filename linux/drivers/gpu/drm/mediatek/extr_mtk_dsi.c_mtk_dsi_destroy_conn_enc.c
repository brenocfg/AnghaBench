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
struct TYPE_2__ {scalar_t__ dev; } ;
struct mtk_dsi {scalar_t__ panel; TYPE_1__ conn; int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 

__attribute__((used)) static void mtk_dsi_destroy_conn_enc(struct mtk_dsi *dsi)
{
	drm_encoder_cleanup(&dsi->encoder);
	/* Skip connector cleanup if creation was delegated to the bridge */
	if (dsi->conn.dev)
		drm_connector_cleanup(&dsi->conn);
	if (dsi->panel)
		drm_panel_detach(dsi->panel);
}