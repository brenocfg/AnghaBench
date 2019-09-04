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

/* Variables and functions */
 unsigned int dw_hdmi_dwc_read (void*,unsigned int) ; 

__attribute__((used)) static int meson_dw_hdmi_reg_read(void *context, unsigned int reg,
				  unsigned int *result)
{
	*result = dw_hdmi_dwc_read(context, reg);

	return 0;

}