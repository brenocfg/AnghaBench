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
typedef  int /*<<< orphan*/  u8 ;
struct stb0899_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODECOEFF ; 
 int /*<<< orphan*/  STB0899_DEMOD ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_get_alpha(struct stb0899_state *state)
{
	u8 mode_coeff;

	mode_coeff = stb0899_read_reg(state, STB0899_DEMOD);

	if (STB0899_GETFIELD(MODECOEFF, mode_coeff) == 1)
		return 20;
	else
		return 35;
}