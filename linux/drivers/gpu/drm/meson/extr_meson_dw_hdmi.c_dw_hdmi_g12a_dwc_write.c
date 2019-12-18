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
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void dw_hdmi_g12a_dwc_write(struct meson_dw_hdmi *dw_hdmi,
					  unsigned int addr, unsigned int data)
{
	writeb(data, dw_hdmi->hdmitx + addr);
}