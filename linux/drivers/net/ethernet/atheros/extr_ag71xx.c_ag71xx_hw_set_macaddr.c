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
struct ag71xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MAC_ADDR1 ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_ADDR2 ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ag71xx_hw_set_macaddr(struct ag71xx *ag, unsigned char *mac)
{
	u32 t;

	t = (((u32)mac[5]) << 24) | (((u32)mac[4]) << 16)
	  | (((u32)mac[3]) << 8) | ((u32)mac[2]);

	ag71xx_wr(ag, AG71XX_REG_MAC_ADDR1, t);

	t = (((u32)mac[1]) << 24) | (((u32)mac[0]) << 16);
	ag71xx_wr(ag, AG71XX_REG_MAC_ADDR2, t);
}