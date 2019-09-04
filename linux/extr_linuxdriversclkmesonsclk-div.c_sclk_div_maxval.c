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
struct TYPE_2__ {int width; } ;
struct meson_sclk_div_data {TYPE_1__ div; } ;

/* Variables and functions */

__attribute__((used)) static int sclk_div_maxval(struct meson_sclk_div_data *sclk)
{
	return (1 << sclk->div.width) - 1;
}