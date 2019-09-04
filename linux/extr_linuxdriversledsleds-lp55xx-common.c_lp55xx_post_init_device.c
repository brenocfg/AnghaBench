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
struct lp55xx_device_config {int (* post_init_device ) (struct lp55xx_chip*) ;} ;
struct lp55xx_chip {struct lp55xx_device_config* cfg; } ;

/* Variables and functions */
 int stub1 (struct lp55xx_chip*) ; 

__attribute__((used)) static int lp55xx_post_init_device(struct lp55xx_chip *chip)
{
	struct lp55xx_device_config *cfg = chip->cfg;

	if (!cfg->post_init_device)
		return 0;

	return cfg->post_init_device(chip);
}