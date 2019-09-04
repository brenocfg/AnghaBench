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
struct meson_dw_hdmi {int dummy; } ;

/* Variables and functions */
 unsigned int dw_hdmi_top_read (struct meson_dw_hdmi*,unsigned int) ; 
 int /*<<< orphan*/  dw_hdmi_top_write (struct meson_dw_hdmi*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void dw_hdmi_top_write_bits(struct meson_dw_hdmi *dw_hdmi,
					  unsigned int addr,
					  unsigned int mask,
					  unsigned int val)
{
	unsigned int data = dw_hdmi_top_read(dw_hdmi, addr);

	data &= ~mask;
	data |= val;

	dw_hdmi_top_write(dw_hdmi, addr, data);
}