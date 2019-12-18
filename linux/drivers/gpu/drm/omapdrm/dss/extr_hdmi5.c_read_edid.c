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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct omap_hdmi {int /*<<< orphan*/  lock; TYPE_1__ wp; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HDMI_WP_SYSCONFIG ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int hdmi5_read_edid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int hdmi_runtime_get (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_runtime_put (struct omap_hdmi*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_edid(struct omap_hdmi *hdmi, u8 *buf, int len)
{
	int r;
	int idlemode;

	mutex_lock(&hdmi->lock);

	r = hdmi_runtime_get(hdmi);
	BUG_ON(r);

	idlemode = REG_GET(hdmi->wp.base, HDMI_WP_SYSCONFIG, 3, 2);
	/* No-idle mode */
	REG_FLD_MOD(hdmi->wp.base, HDMI_WP_SYSCONFIG, 1, 3, 2);

	r = hdmi5_read_edid(&hdmi->core,  buf, len);

	REG_FLD_MOD(hdmi->wp.base, HDMI_WP_SYSCONFIG, idlemode, 3, 2);

	hdmi_runtime_put(hdmi);
	mutex_unlock(&hdmi->lock);

	return r;
}