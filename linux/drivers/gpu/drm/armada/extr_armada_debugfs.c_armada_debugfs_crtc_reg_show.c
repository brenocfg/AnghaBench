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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {struct armada_crtc* private; } ;
struct armada_crtc {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada_debugfs_crtc_reg_show(struct seq_file *m, void *data)
{
	struct armada_crtc *dcrtc = m->private;
	int i;

	for (i = 0x84; i <= 0x1c4; i += 4) {
		u32 v = readl_relaxed(dcrtc->base + i);
		seq_printf(m, "0x%04x: 0x%08x\n", i, v);
	}

	return 0;
}