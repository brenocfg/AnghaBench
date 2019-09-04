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
typedef  short u16 ;
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dib3000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MB_REG_NOISE_POWER_LSB ; 
 int /*<<< orphan*/  DIB3000MB_REG_NOISE_POWER_MSB ; 
 int /*<<< orphan*/  DIB3000MB_REG_SIGNAL_POWER ; 
 int rd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib3000mb_read_snr(struct dvb_frontend* fe, u16 *snr)
{
	struct dib3000_state* state = fe->demodulator_priv;
	short sigpow = rd(DIB3000MB_REG_SIGNAL_POWER);
	int icipow = ((rd(DIB3000MB_REG_NOISE_POWER_MSB) & 0xff) << 16) |
		rd(DIB3000MB_REG_NOISE_POWER_LSB);
	*snr = (sigpow << 8) / ((icipow > 0) ? icipow : 1);
	return 0;
}