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
struct da9034_touch {int /*<<< orphan*/  da9034_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9034_AUTO_CTRL2 ; 
 int /*<<< orphan*/  DA9034_AUTO_TSI_EN ; 
 int da903x_clr_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int stop_tsi(struct da9034_touch *touch)
{
	return da903x_clr_bits(touch->da9034_dev,
			DA9034_AUTO_CTRL2, DA9034_AUTO_TSI_EN);
}