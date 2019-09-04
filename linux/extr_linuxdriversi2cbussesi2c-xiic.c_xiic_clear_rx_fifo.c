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
typedef  int u8 ;
struct xiic_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XIIC_DRR_REG_OFFSET ; 
 int /*<<< orphan*/  XIIC_SR_REG_OFFSET ; 
 int XIIC_SR_RX_FIFO_EMPTY_MASK ; 
 int xiic_getreg8 (struct xiic_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xiic_clear_rx_fifo(struct xiic_i2c *i2c)
{
	u8 sr;
	for (sr = xiic_getreg8(i2c, XIIC_SR_REG_OFFSET);
		!(sr & XIIC_SR_RX_FIFO_EMPTY_MASK);
		sr = xiic_getreg8(i2c, XIIC_SR_REG_OFFSET))
		xiic_getreg8(i2c, XIIC_DRR_REG_OFFSET);
}