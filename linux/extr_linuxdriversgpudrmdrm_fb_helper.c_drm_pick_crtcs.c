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
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct drm_fb_helper_crtc {TYPE_1__ mode_set; } ;
struct drm_fb_helper_connector {struct drm_connector* connector; } ;
struct drm_fb_helper {int connector_count; int crtc_count; struct drm_fb_helper_crtc* crtc_info; struct drm_fb_helper_connector** connector_info; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  connector_has_possible_crtc (struct drm_connector*,int /*<<< orphan*/ ) ; 
 scalar_t__ connector_status_connected ; 
 scalar_t__ drm_has_cmdline_mode (struct drm_fb_helper_connector*) ; 
 scalar_t__ drm_has_preferred_mode (struct drm_fb_helper_connector*,int,int) ; 
 int /*<<< orphan*/  drm_mode_equal (struct drm_display_mode*,struct drm_display_mode*) ; 
 struct drm_fb_helper_crtc** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_fb_helper_crtc**) ; 
 int /*<<< orphan*/  memcpy (struct drm_fb_helper_crtc**,struct drm_fb_helper_crtc**,int) ; 

__attribute__((used)) static int drm_pick_crtcs(struct drm_fb_helper *fb_helper,
			  struct drm_fb_helper_crtc **best_crtcs,
			  struct drm_display_mode **modes,
			  int n, int width, int height)
{
	int c, o;
	struct drm_connector *connector;
	int my_score, best_score, score;
	struct drm_fb_helper_crtc **crtcs, *crtc;
	struct drm_fb_helper_connector *fb_helper_conn;

	if (n == fb_helper->connector_count)
		return 0;

	fb_helper_conn = fb_helper->connector_info[n];
	connector = fb_helper_conn->connector;

	best_crtcs[n] = NULL;
	best_score = drm_pick_crtcs(fb_helper, best_crtcs, modes, n+1, width, height);
	if (modes[n] == NULL)
		return best_score;

	crtcs = kcalloc(fb_helper->connector_count,
			sizeof(struct drm_fb_helper_crtc *), GFP_KERNEL);
	if (!crtcs)
		return best_score;

	my_score = 1;
	if (connector->status == connector_status_connected)
		my_score++;
	if (drm_has_cmdline_mode(fb_helper_conn))
		my_score++;
	if (drm_has_preferred_mode(fb_helper_conn, width, height))
		my_score++;

	/*
	 * select a crtc for this connector and then attempt to configure
	 * remaining connectors
	 */
	for (c = 0; c < fb_helper->crtc_count; c++) {
		crtc = &fb_helper->crtc_info[c];

		if (!connector_has_possible_crtc(connector,
						 crtc->mode_set.crtc))
			continue;

		for (o = 0; o < n; o++)
			if (best_crtcs[o] == crtc)
				break;

		if (o < n) {
			/* ignore cloning unless only a single crtc */
			if (fb_helper->crtc_count > 1)
				continue;

			if (!drm_mode_equal(modes[o], modes[n]))
				continue;
		}

		crtcs[n] = crtc;
		memcpy(crtcs, best_crtcs, n * sizeof(struct drm_fb_helper_crtc *));
		score = my_score + drm_pick_crtcs(fb_helper, crtcs, modes, n + 1,
						  width, height);
		if (score > best_score) {
			best_score = score;
			memcpy(best_crtcs, crtcs,
			       fb_helper->connector_count *
			       sizeof(struct drm_fb_helper_crtc *));
		}
	}

	kfree(crtcs);
	return best_score;
}