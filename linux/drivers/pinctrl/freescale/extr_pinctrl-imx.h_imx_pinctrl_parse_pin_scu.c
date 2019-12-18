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
struct imx_pinctrl {int dummy; } ;
struct imx_pin {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */

__attribute__((used)) static inline void imx_pinctrl_parse_pin_scu(struct imx_pinctrl *ipctl,
					    unsigned int *pin_id,
					    struct imx_pin *pin,
					    const __be32 **list_p)
{
}