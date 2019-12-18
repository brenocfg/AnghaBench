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
typedef  int u32 ;
struct reset_controller_dev {int dummy; } ;
struct lpc18xx_rgu_data {int base; } ;

/* Variables and functions */
 int LPC18XX_RGU_ACTIVE_STATUS0 ; 
 unsigned long LPC18XX_RGU_RESETS_PER_REG ; 
 int readl (int) ; 
 struct lpc18xx_rgu_data* to_rgu_data (struct reset_controller_dev*) ; 

__attribute__((used)) static int lpc18xx_rgu_status(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	struct lpc18xx_rgu_data *rc = to_rgu_data(rcdev);
	u32 bit, offset = LPC18XX_RGU_ACTIVE_STATUS0;

	offset += (id / LPC18XX_RGU_RESETS_PER_REG) * sizeof(u32);
	bit = 1 << (id % LPC18XX_RGU_RESETS_PER_REG);

	return !(readl(rc->base + offset) & bit);
}