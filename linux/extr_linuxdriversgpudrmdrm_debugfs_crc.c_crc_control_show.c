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
struct seq_file {struct drm_crtc* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;
struct drm_crtc {TYPE_1__ crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crc_control_show(struct seq_file *m, void *data)
{
	struct drm_crtc *crtc = m->private;

	seq_printf(m, "%s\n", crtc->crc.source);

	return 0;
}