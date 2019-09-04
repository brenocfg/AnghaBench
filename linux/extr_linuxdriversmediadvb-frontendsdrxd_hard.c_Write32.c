#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int demod_address; } ;
struct drxd_state {int /*<<< orphan*/  i2c; TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ i2c_write (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int Write32(struct drxd_state *state, u32 reg, u32 data, u8 flags)
{
	u8 adr = state->config.demod_address;
	u8 mm[8] = { reg & 0xff, (reg >> 16) & 0xff,
		flags | ((reg >> 24) & 0xff), (reg >> 8) & 0xff,
		data & 0xff, (data >> 8) & 0xff,
		(data >> 16) & 0xff, (data >> 24) & 0xff
	};

	if (i2c_write(state->i2c, adr, mm, 8) < 0)
		return -1;
	return 0;
}