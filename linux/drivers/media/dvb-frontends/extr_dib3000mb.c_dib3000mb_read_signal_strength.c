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
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dib3000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MB_REG_SIGNAL_POWER ; 
 int rd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib3000mb_read_signal_strength(struct dvb_frontend* fe, u16 *strength)
{
	struct dib3000_state* state = fe->demodulator_priv;

	*strength = rd(DIB3000MB_REG_SIGNAL_POWER) * 0xffff / 0x170;
	return 0;
}