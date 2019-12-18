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
struct meson_dw_hdmi {TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dwc_write ) (struct meson_dw_hdmi*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct meson_dw_hdmi*,unsigned int,unsigned int) ; 

__attribute__((used)) static int meson_dw_hdmi_reg_write(void *context, unsigned int reg,
				   unsigned int val)
{
	struct meson_dw_hdmi *dw_hdmi = context;

	dw_hdmi->data->dwc_write(dw_hdmi, reg, val);

	return 0;
}