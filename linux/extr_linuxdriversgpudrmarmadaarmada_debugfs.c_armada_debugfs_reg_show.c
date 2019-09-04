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
typedef  int /*<<< orphan*/  uint32_t ;
struct seq_file {struct drm_device* private; } ;
struct drm_device {struct armada_private* dev_private; } ;
struct armada_private {struct armada_crtc** dcrtc; } ;
struct armada_crtc {scalar_t__ base; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct armada_crtc**) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada_debugfs_reg_show(struct seq_file *m, void *data)
{
	struct drm_device *dev = m->private;
	struct armada_private *priv = dev->dev_private;
	int n, i;

	if (priv) {
		for (n = 0; n < ARRAY_SIZE(priv->dcrtc); n++) {
			struct armada_crtc *dcrtc = priv->dcrtc[n];
			if (!dcrtc)
				continue;

			for (i = 0x84; i <= 0x1c4; i += 4) {
				uint32_t v = readl_relaxed(dcrtc->base + i);
				seq_printf(m, "%u: 0x%04x: 0x%08x\n", n, i, v);
			}
		}
	}

	return 0;
}