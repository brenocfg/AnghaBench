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
struct reset_controller_dev {int dummy; } ;
struct lpc18xx_rgu_data {int /*<<< orphan*/  delay_us; } ;

/* Variables and functions */
#define  LPC43XX_RGU_M0APP_RST 129 
#define  LPC43XX_RGU_M0SUB_RST 128 
 int /*<<< orphan*/  lpc18xx_rgu_assert (struct reset_controller_dev*,unsigned long) ; 
 int /*<<< orphan*/  lpc18xx_rgu_setclear_reset (struct reset_controller_dev*,unsigned long,int) ; 
 struct lpc18xx_rgu_data* to_rgu_data (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc18xx_rgu_reset(struct reset_controller_dev *rcdev,
			     unsigned long id)
{
	struct lpc18xx_rgu_data *rc = to_rgu_data(rcdev);

	lpc18xx_rgu_assert(rcdev, id);
	udelay(rc->delay_us);

	switch (id) {
	case LPC43XX_RGU_M0SUB_RST:
	case LPC43XX_RGU_M0APP_RST:
		lpc18xx_rgu_setclear_reset(rcdev, id, false);
	}

	return 0;
}