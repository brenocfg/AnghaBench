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
struct dw_hdmi_phy_ops {int dummy; } ;

/* Variables and functions */
 struct dw_hdmi_phy_ops const sun8i_hdmi_phy_ops ; 

const struct dw_hdmi_phy_ops *sun8i_hdmi_phy_get_ops(void)
{
	return &sun8i_hdmi_phy_ops;
}