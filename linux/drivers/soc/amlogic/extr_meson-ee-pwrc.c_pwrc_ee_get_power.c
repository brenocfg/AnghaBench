#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {TYPE_2__* top_pd; } ;
struct meson_ee_pwrc_domain {TYPE_3__ desc; TYPE_1__* pwrc; } ;
struct TYPE_5__ {int sleep_mask; int /*<<< orphan*/  sleep_reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap_ao; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool pwrc_ee_get_power(struct meson_ee_pwrc_domain *pwrc_domain)
{
	u32 reg;

	regmap_read(pwrc_domain->pwrc->regmap_ao,
		    pwrc_domain->desc.top_pd->sleep_reg, &reg);

	return (reg & pwrc_domain->desc.top_pd->sleep_mask);
}