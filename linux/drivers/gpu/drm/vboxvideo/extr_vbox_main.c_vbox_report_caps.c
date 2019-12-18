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
typedef  int u32 ;
struct vbox_private {int /*<<< orphan*/  guest_pool; } ;

/* Variables and functions */
 int VBVACAPS_DISABLE_CURSOR_INTEGRATION ; 
 int VBVACAPS_IRQ ; 
 int VBVACAPS_USE_VBVA_ONLY ; 
 int VBVACAPS_VIDEO_MODE_HINTS ; 
 int /*<<< orphan*/  hgsmi_send_caps_info (int /*<<< orphan*/ ,int) ; 

void vbox_report_caps(struct vbox_private *vbox)
{
	u32 caps = VBVACAPS_DISABLE_CURSOR_INTEGRATION |
		   VBVACAPS_IRQ | VBVACAPS_USE_VBVA_ONLY;

	/* The host only accepts VIDEO_MODE_HINTS if it is send separately. */
	hgsmi_send_caps_info(vbox->guest_pool, caps);
	caps |= VBVACAPS_VIDEO_MODE_HINTS;
	hgsmi_send_caps_info(vbox->guest_pool, caps);
}