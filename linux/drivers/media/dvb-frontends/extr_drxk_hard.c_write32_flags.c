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
struct drxk_state {int demod_address; scalar_t__ single_master; } ;

/* Variables and functions */
 scalar_t__ DRXDAP_FASI_LONG_FORMAT (int) ; 
 int /*<<< orphan*/  dprintk (int,char*,int,int,int) ; 
 int i2c_write (struct drxk_state*,int,int*,int) ; 

__attribute__((used)) static int write32_flags(struct drxk_state *state, u32 reg, u32 data, u8 flags)
{
	u8 adr = state->demod_address, mm[8], len;

	if (state->single_master)
		flags |= 0xC0;
	if (DRXDAP_FASI_LONG_FORMAT(reg) || (flags != 0)) {
		mm[0] = (((reg << 1) & 0xFF) | 0x01);
		mm[1] = ((reg >> 16) & 0xFF);
		mm[2] = ((reg >> 24) & 0xFF) | flags;
		mm[3] = ((reg >> 7) & 0xFF);
		len = 4;
	} else {
		mm[0] = ((reg << 1) & 0xFF);
		mm[1] = (((reg >> 16) & 0x0F) | ((reg >> 18) & 0xF0));
		len = 2;
	}
	mm[len] = data & 0xff;
	mm[len + 1] = (data >> 8) & 0xff;
	mm[len + 2] = (data >> 16) & 0xff;
	mm[len + 3] = (data >> 24) & 0xff;
	dprintk(2, "(0x%08x, 0x%08x, 0x%02x)\n", reg, data, flags);

	return i2c_write(state, adr, mm, len + 4);
}