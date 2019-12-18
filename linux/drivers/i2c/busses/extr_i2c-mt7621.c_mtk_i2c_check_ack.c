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
struct mtk_i2c {scalar_t__ base; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ REG_SM0CTL1_REG ; 
 int SM0CTL1_ACK_MASK ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int mtk_i2c_check_ack(struct mtk_i2c *i2c, u32 expected)
{
	u32 ack = readl_relaxed(i2c->base + REG_SM0CTL1_REG);
	u32 ack_expected = (expected << 16) & SM0CTL1_ACK_MASK;

	return ((ack & ack_expected) == ack_expected) ? 0 : -ENXIO;
}