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
struct stimx274 {int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX274_RESET_DELAY1 ; 
 int /*<<< orphan*/  IMX274_RESET_DELAY2 ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx274_reset(struct stimx274 *priv, int rst)
{
	gpiod_set_value_cansleep(priv->reset_gpio, 0);
	usleep_range(IMX274_RESET_DELAY1, IMX274_RESET_DELAY2);
	gpiod_set_value_cansleep(priv->reset_gpio, !!rst);
	usleep_range(IMX274_RESET_DELAY1, IMX274_RESET_DELAY2);
}