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
struct msm_kms {TYPE_2__* funcs; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct hdmi_platform_config {scalar_t__ pwr_clk_cnt; } ;
struct hdmi_connector {struct hdmi* hdmi; } ;
struct hdmi {int /*<<< orphan*/ * pwr_clks; int /*<<< orphan*/  encoder; struct hdmi_platform_config* config; } ;
struct drm_display_mode {int clock; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct TYPE_4__ {long (* round_pixclk ) (struct msm_kms*,long,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,long,long) ; 
 int MODE_CLOCK_RANGE ; 
 long clk_round_rate (int /*<<< orphan*/ ,long) ; 
 long stub1 (struct msm_kms*,long,int /*<<< orphan*/ ) ; 
 struct hdmi_connector* to_hdmi_connector (struct drm_connector*) ; 

__attribute__((used)) static int msm_hdmi_connector_mode_valid(struct drm_connector *connector,
				 struct drm_display_mode *mode)
{
	struct hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	struct hdmi *hdmi = hdmi_connector->hdmi;
	const struct hdmi_platform_config *config = hdmi->config;
	struct msm_drm_private *priv = connector->dev->dev_private;
	struct msm_kms *kms = priv->kms;
	long actual, requested;

	requested = 1000 * mode->clock;
	actual = kms->funcs->round_pixclk(kms,
			requested, hdmi_connector->hdmi->encoder);

	/* for mdp5/apq8074, we manage our own pixel clk (as opposed to
	 * mdp4/dtv stuff where pixel clk is assigned to mdp/encoder
	 * instead):
	 */
	if (config->pwr_clk_cnt > 0)
		actual = clk_round_rate(hdmi->pwr_clks[0], actual);

	DBG("requested=%ld, actual=%ld", requested, actual);

	if (actual != requested)
		return MODE_CLOCK_RANGE;

	return 0;
}