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
typedef  unsigned int u32 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSIO_MCB_S6G_ADDR_CFG ; 
 unsigned int HSIO_MCB_S6G_ADDR_CFG_SERDES6G_ADDR (int /*<<< orphan*/ ) ; 
 int MCB_S6G_CFG_TIMEOUT ; 
 int regmap_read_poll_timeout (struct regmap*,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int __serdes_write_mcb_s6g(struct regmap *regmap, u8 macro, u32 op)
{
	unsigned int regval = 0;

	regmap_write(regmap, HSIO_MCB_S6G_ADDR_CFG, op |
		     HSIO_MCB_S6G_ADDR_CFG_SERDES6G_ADDR(BIT(macro)));

	return regmap_read_poll_timeout(regmap, HSIO_MCB_S6G_ADDR_CFG, regval,
					(regval & op) != op, 100,
					MCB_S6G_CFG_TIMEOUT * 1000);
}