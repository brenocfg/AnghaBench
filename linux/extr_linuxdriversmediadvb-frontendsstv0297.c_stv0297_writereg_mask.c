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
struct stv0297_state {int dummy; } ;

/* Variables and functions */
 int stv0297_readreg (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_writereg (struct stv0297_state*,int,int) ; 

__attribute__((used)) static int stv0297_writereg_mask(struct stv0297_state *state, u8 reg, u8 mask, u8 data)
{
	int val;

	val = stv0297_readreg(state, reg);
	val &= ~mask;
	val |= (data & mask);
	stv0297_writereg(state, reg, val);

	return 0;
}