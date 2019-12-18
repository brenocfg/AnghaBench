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
typedef  scalar_t__ u8 ;
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALIDP550_CONFIG_VALID ; 
 int /*<<< orphan*/  MALIDP_CFG_VALID ; 
 int /*<<< orphan*/  malidp_hw_clearbits (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_setbits (struct malidp_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void malidp550_set_config_valid(struct malidp_hw_device *hwdev, u8 value)
{
	if (value)
		malidp_hw_setbits(hwdev, MALIDP_CFG_VALID, MALIDP550_CONFIG_VALID);
	else
		malidp_hw_clearbits(hwdev, MALIDP_CFG_VALID, MALIDP550_CONFIG_VALID);
}