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
typedef  int u16 ;
struct dib9000_state {int dummy; } ;

/* Variables and functions */
 int dib9000_write16_attr (struct dib9000_state*,int,int*,int,int) ; 

__attribute__((used)) static inline int dib9000_write_word_attr(struct dib9000_state *state, u16 reg, u16 val, u16 attribute)
{
	u8 b[2] = { val >> 8, val & 0xff };
	return dib9000_write16_attr(state, reg, b, 2, attribute);
}