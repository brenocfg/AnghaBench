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
struct TYPE_2__ {unsigned int (* dwc_read ) (struct meson_dw_hdmi*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int stub1 (struct meson_dw_hdmi*,unsigned int) ; 

__attribute__((used)) static int meson_dw_hdmi_reg_read(void *context, unsigned int reg,
				  unsigned int *result)
{
	struct meson_dw_hdmi *dw_hdmi = context;

	*result = dw_hdmi->data->dwc_read(dw_hdmi, reg);

	return 0;

}