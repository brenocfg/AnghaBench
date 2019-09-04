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
 int /*<<< orphan*/  dprintk (int,char*,int,int) ; 
 int i2c_read (struct drxk_state*,int,int*,int,int*,int) ; 

__attribute__((used)) static int read32_flags(struct drxk_state *state, u32 reg, u32 *data, u8 flags)
{
	int status;
	u8 adr = state->demod_address, mm1[4], mm2[4], len;

	if (state->single_master)
		flags |= 0xC0;

	if (DRXDAP_FASI_LONG_FORMAT(reg) || (flags != 0)) {
		mm1[0] = (((reg << 1) & 0xFF) | 0x01);
		mm1[1] = ((reg >> 16) & 0xFF);
		mm1[2] = ((reg >> 24) & 0xFF) | flags;
		mm1[3] = ((reg >> 7) & 0xFF);
		len = 4;
	} else {
		mm1[0] = ((reg << 1) & 0xFF);
		mm1[1] = (((reg >> 16) & 0x0F) | ((reg >> 18) & 0xF0));
		len = 2;
	}
	dprintk(2, "(0x%08x, 0x%02x)\n", reg, flags);
	status = i2c_read(state, adr, mm1, len, mm2, 4);
	if (status < 0)
		return status;
	if (data)
		*data = mm2[0] | (mm2[1] << 8) |
		    (mm2[2] << 16) | (mm2[3] << 24);

	return 0;
}