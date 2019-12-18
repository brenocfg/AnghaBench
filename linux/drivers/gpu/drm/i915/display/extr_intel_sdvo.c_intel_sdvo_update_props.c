#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  dot_crawl; int /*<<< orphan*/  luma_filter; int /*<<< orphan*/  chroma_filter; int /*<<< orphan*/  flicker_filter_adaptive; int /*<<< orphan*/  flicker_filter_2d; int /*<<< orphan*/  flicker_filter; int /*<<< orphan*/  sharpness; int /*<<< orphan*/  vpos; int /*<<< orphan*/  hpos; int /*<<< orphan*/  overscan_v; int /*<<< orphan*/  overscan_h; } ;
struct TYPE_5__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  hue; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; } ;
struct drm_connector_state {TYPE_2__ tv; int /*<<< orphan*/  connector; } ;
struct TYPE_4__ {struct drm_connector_state base; } ;
struct intel_sdvo_connector_state {TYPE_3__ tv; TYPE_1__ base; } ;
struct intel_sdvo_connector {scalar_t__ dot_crawl; scalar_t__ tv_luma_filter; scalar_t__ tv_chroma_filter; scalar_t__ flicker_filter_adaptive; scalar_t__ flicker_filter_2d; scalar_t__ flicker_filter; scalar_t__ sharpness; scalar_t__ brightness; scalar_t__ hue; scalar_t__ contrast; scalar_t__ saturation; scalar_t__ vpos; scalar_t__ hpos; scalar_t__ top; scalar_t__ left; } ;
struct intel_sdvo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIGHTNESS ; 
 int /*<<< orphan*/  CONTRAST ; 
 int /*<<< orphan*/  DOT_CRAWL ; 
 int /*<<< orphan*/  FLICKER_FILTER ; 
 int /*<<< orphan*/  FLICKER_FILTER_2D ; 
 int /*<<< orphan*/  FLICKER_FILTER_ADAPTIVE ; 
 int /*<<< orphan*/  HPOS ; 
 int /*<<< orphan*/  HUE ; 
 int /*<<< orphan*/  OVERSCAN_H ; 
 int /*<<< orphan*/  OVERSCAN_V ; 
 int /*<<< orphan*/  SATURATION ; 
 int /*<<< orphan*/  SHARPNESS ; 
 int /*<<< orphan*/  TV_CHROMA_FILTER ; 
 int /*<<< orphan*/  TV_LUMA_FILTER ; 
 int /*<<< orphan*/  UPDATE_PROPERTY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPOS ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_sdvo_update_props(struct intel_sdvo *intel_sdvo,
				    const struct intel_sdvo_connector_state *sdvo_state)
{
	const struct drm_connector_state *conn_state = &sdvo_state->base.base;
	struct intel_sdvo_connector *intel_sdvo_conn =
		to_intel_sdvo_connector(conn_state->connector);
	u16 val;

	if (intel_sdvo_conn->left)
		UPDATE_PROPERTY(sdvo_state->tv.overscan_h, OVERSCAN_H);

	if (intel_sdvo_conn->top)
		UPDATE_PROPERTY(sdvo_state->tv.overscan_v, OVERSCAN_V);

	if (intel_sdvo_conn->hpos)
		UPDATE_PROPERTY(sdvo_state->tv.hpos, HPOS);

	if (intel_sdvo_conn->vpos)
		UPDATE_PROPERTY(sdvo_state->tv.vpos, VPOS);

	if (intel_sdvo_conn->saturation)
		UPDATE_PROPERTY(conn_state->tv.saturation, SATURATION);

	if (intel_sdvo_conn->contrast)
		UPDATE_PROPERTY(conn_state->tv.contrast, CONTRAST);

	if (intel_sdvo_conn->hue)
		UPDATE_PROPERTY(conn_state->tv.hue, HUE);

	if (intel_sdvo_conn->brightness)
		UPDATE_PROPERTY(conn_state->tv.brightness, BRIGHTNESS);

	if (intel_sdvo_conn->sharpness)
		UPDATE_PROPERTY(sdvo_state->tv.sharpness, SHARPNESS);

	if (intel_sdvo_conn->flicker_filter)
		UPDATE_PROPERTY(sdvo_state->tv.flicker_filter, FLICKER_FILTER);

	if (intel_sdvo_conn->flicker_filter_2d)
		UPDATE_PROPERTY(sdvo_state->tv.flicker_filter_2d, FLICKER_FILTER_2D);

	if (intel_sdvo_conn->flicker_filter_adaptive)
		UPDATE_PROPERTY(sdvo_state->tv.flicker_filter_adaptive, FLICKER_FILTER_ADAPTIVE);

	if (intel_sdvo_conn->tv_chroma_filter)
		UPDATE_PROPERTY(sdvo_state->tv.chroma_filter, TV_CHROMA_FILTER);

	if (intel_sdvo_conn->tv_luma_filter)
		UPDATE_PROPERTY(sdvo_state->tv.luma_filter, TV_LUMA_FILTER);

	if (intel_sdvo_conn->dot_crawl)
		UPDATE_PROPERTY(sdvo_state->tv.dot_crawl, DOT_CRAWL);

#undef UPDATE_PROPERTY
}