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
typedef  int u16 ;
struct dib9000_state {int* i2c_read_buffer; } ;

/* Variables and functions */
 scalar_t__ dib9000_read16_attr (struct dib9000_state*,int,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 dib9000_read_word(struct dib9000_state *state, u16 reg)
{
	if (dib9000_read16_attr(state, reg, state->i2c_read_buffer, 2, 0) != 0)
		return 0;
	return (state->i2c_read_buffer[0] << 8) | state->i2c_read_buffer[1];
}