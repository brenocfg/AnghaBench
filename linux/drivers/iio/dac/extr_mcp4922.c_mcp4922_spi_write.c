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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct mcp4922_state {int* mosi; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int spi_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mcp4922_spi_write(struct mcp4922_state *state, u8 addr, u32 val)
{
	state->mosi[1] = val & 0xff;
	state->mosi[0] = (addr == 0) ? 0x00 : 0x80;
	state->mosi[0] |= 0x30 | ((val >> 8) & 0x0f);

	return spi_write(state->spi, state->mosi, 2);
}