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
struct TYPE_2__ {int link; } ;
struct fixed_phy {scalar_t__ link_gpiod; TYPE_1__ status; int /*<<< orphan*/  no_carrier; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_get_value_cansleep (scalar_t__) ; 

__attribute__((used)) static void fixed_phy_update(struct fixed_phy *fp)
{
	if (!fp->no_carrier && fp->link_gpiod)
		fp->status.link = !!gpiod_get_value_cansleep(fp->link_gpiod);
}