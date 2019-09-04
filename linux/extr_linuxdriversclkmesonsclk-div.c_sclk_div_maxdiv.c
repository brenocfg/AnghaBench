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
struct meson_sclk_div_data {int dummy; } ;

/* Variables and functions */
 int sclk_div_maxval (struct meson_sclk_div_data*) ; 

__attribute__((used)) static int sclk_div_maxdiv(struct meson_sclk_div_data *sclk)
{
	return sclk_div_maxval(sclk) + 1;
}