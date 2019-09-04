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
struct link_params {int /*<<< orphan*/  port; int /*<<< orphan*/  bp; } ;
struct bnx2x_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_1 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_2 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_OUTPUT_LOW ; 
 int /*<<< orphan*/  bnx2x_set_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_7101_hw_reset(struct bnx2x_phy *phy,
				struct link_params *params) {
	/* Low power mode is controlled by GPIO 2 */
	bnx2x_set_gpio(params->bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, params->port);
	/* The PHY reset is controlled by GPIO 1 */
	bnx2x_set_gpio(params->bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, params->port);
}