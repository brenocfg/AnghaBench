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
struct mtk_i2c {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_SM0CTL1_REG ; 
 int SM0CTL1_START ; 
 int SM0CTL1_TRI ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int mtk_i2c_wait_idle (struct mtk_i2c*) ; 

__attribute__((used)) static int mtk_i2c_master_start(struct mtk_i2c *i2c)
{
	iowrite32(SM0CTL1_START | SM0CTL1_TRI, i2c->base + REG_SM0CTL1_REG);
	return mtk_i2c_wait_idle(i2c);
}