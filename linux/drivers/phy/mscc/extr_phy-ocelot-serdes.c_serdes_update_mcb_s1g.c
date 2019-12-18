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
typedef  int /*<<< orphan*/  u8 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSIO_MCB_S1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT ; 
 int __serdes_write_mcb_s1g (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int serdes_update_mcb_s1g(struct regmap *regmap, u8 macro)
{
	return __serdes_write_mcb_s1g(regmap, macro,
		HSIO_MCB_S1G_ADDR_CFG_SERDES1G_RD_ONE_SHOT);
}