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
typedef  int u32 ;
struct stv0367_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  extract_mask_pos (int,int*,int*) ; 
 int stv0367_readreg (struct stv0367_state*,int) ; 
 int /*<<< orphan*/  stv0367_writereg (struct stv0367_state*,int,int) ; 

__attribute__((used)) static void stv0367_writebits(struct stv0367_state *state, u32 label, u8 val)
{
	u8 reg, mask, pos;

	reg = stv0367_readreg(state, (label >> 16) & 0xffff);
	extract_mask_pos(label, &mask, &pos);

	val = mask & (val << pos);

	reg = (reg & (~mask)) | val;
	stv0367_writereg(state, (label >> 16) & 0xffff, reg);

}