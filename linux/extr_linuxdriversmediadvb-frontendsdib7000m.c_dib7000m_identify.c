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
struct dib7000m_state {int revision; int reg_offs; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int dib7000m_read_word (struct dib7000m_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static int dib7000m_identify(struct dib7000m_state *state)
{
	u16 value;

	if ((value = dib7000m_read_word(state, 896)) != 0x01b3) {
		dprintk("wrong Vendor ID (0x%x)\n", value);
		return -EREMOTEIO;
	}

	state->revision = dib7000m_read_word(state, 897);
	if (state->revision != 0x4000 &&
		state->revision != 0x4001 &&
		state->revision != 0x4002 &&
		state->revision != 0x4003) {
		dprintk("wrong Device ID (0x%x)\n", value);
		return -EREMOTEIO;
	}

	/* protect this driver to be used with 7000PC */
	if (state->revision == 0x4000 && dib7000m_read_word(state, 769) == 0x4000) {
		dprintk("this driver does not work with DiB7000PC\n");
		return -EREMOTEIO;
	}

	switch (state->revision) {
	case 0x4000: dprintk("found DiB7000MA/PA/MB/PB\n"); break;
	case 0x4001: state->reg_offs = 1; dprintk("found DiB7000HC\n"); break;
	case 0x4002: state->reg_offs = 1; dprintk("found DiB7000MC\n"); break;
	case 0x4003: state->reg_offs = 1; dprintk("found DiB9000\n"); break;
	}

	return 0;
}