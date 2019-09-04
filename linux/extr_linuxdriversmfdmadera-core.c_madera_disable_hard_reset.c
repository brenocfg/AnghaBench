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
struct TYPE_2__ {int /*<<< orphan*/  reset; } ;
struct madera {TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_raw_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void madera_disable_hard_reset(struct madera *madera)
{
	if (!madera->pdata.reset)
		return;

	gpiod_set_raw_value_cansleep(madera->pdata.reset, 1);
	usleep_range(1000, 2000);
}