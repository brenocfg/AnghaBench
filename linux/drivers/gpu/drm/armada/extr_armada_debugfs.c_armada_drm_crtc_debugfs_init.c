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
struct TYPE_2__ {int /*<<< orphan*/  debugfs_entry; } ;
struct armada_crtc {TYPE_1__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  armada_debugfs_crtc_reg_fops ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct armada_crtc*,int /*<<< orphan*/ *) ; 

void armada_drm_crtc_debugfs_init(struct armada_crtc *dcrtc)
{
	debugfs_create_file("armada-regs", 0600, dcrtc->crtc.debugfs_entry,
			    dcrtc, &armada_debugfs_crtc_reg_fops);
}