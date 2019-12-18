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
struct imx_pinctrl {scalar_t__ pctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_unregister (scalar_t__) ; 

__attribute__((used)) static void imx_free_resources(struct imx_pinctrl *ipctl)
{
	if (ipctl->pctl)
		pinctrl_unregister(ipctl->pctl);
}