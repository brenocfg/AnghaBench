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
struct meson_dw_hdmi {scalar_t__ hdmitx; } ;

/* Variables and functions */
 unsigned int readb (scalar_t__) ; 

__attribute__((used)) static unsigned int dw_hdmi_g12a_dwc_read(struct meson_dw_hdmi *dw_hdmi,
					  unsigned int addr)
{
	return readb(dw_hdmi->hdmitx + addr);
}