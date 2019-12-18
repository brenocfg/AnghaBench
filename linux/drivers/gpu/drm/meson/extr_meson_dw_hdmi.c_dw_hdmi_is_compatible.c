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
struct meson_dw_hdmi {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int of_device_is_compatible (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline int dw_hdmi_is_compatible(struct meson_dw_hdmi *dw_hdmi,
					const char *compat)
{
	return of_device_is_compatible(dw_hdmi->dev->of_node, compat);
}