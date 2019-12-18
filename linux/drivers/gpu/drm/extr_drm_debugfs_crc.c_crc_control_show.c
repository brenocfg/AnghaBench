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
struct seq_file {struct drm_crtc* private; } ;
struct TYPE_4__ {char const* const source; } ;
struct drm_crtc {TYPE_2__ crc; TYPE_1__* funcs; } ;
struct TYPE_3__ {char** (* get_crc_sources ) (struct drm_crtc*,size_t*) ;int /*<<< orphan*/  (* verify_crc_source ) (struct drm_crtc*,char const* const,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const* const) ; 
 scalar_t__ strcmp (char const* const,char const* const) ; 
 char** stub1 (struct drm_crtc*,size_t*) ; 
 int /*<<< orphan*/  stub2 (struct drm_crtc*,char const* const,size_t*) ; 

__attribute__((used)) static int crc_control_show(struct seq_file *m, void *data)
{
	struct drm_crtc *crtc = m->private;

	if (crtc->funcs->get_crc_sources) {
		size_t count;
		const char *const *sources = crtc->funcs->get_crc_sources(crtc,
									&count);
		size_t values_cnt;
		int i;

		if (count == 0 || !sources)
			goto out;

		for (i = 0; i < count; i++)
			if (!crtc->funcs->verify_crc_source(crtc, sources[i],
							    &values_cnt)) {
				if (strcmp(sources[i], crtc->crc.source))
					seq_printf(m, "%s\n", sources[i]);
				else
					seq_printf(m, "%s*\n", sources[i]);
			}
	}
	return 0;

out:
	seq_printf(m, "%s*\n", crtc->crc.source);
	return 0;
}