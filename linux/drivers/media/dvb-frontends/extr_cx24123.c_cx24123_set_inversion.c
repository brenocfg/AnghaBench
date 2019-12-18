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
struct cx24123_state {int dummy; } ;
typedef  enum fe_spectral_inversion { ____Placeholder_fe_spectral_inversion } fe_spectral_inversion ;

/* Variables and functions */
 int EINVAL ; 
#define  INVERSION_AUTO 130 
#define  INVERSION_OFF 129 
#define  INVERSION_ON 128 
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  cx24123_writereg (struct cx24123_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int cx24123_set_inversion(struct cx24123_state *state,
				 enum fe_spectral_inversion inversion)
{
	u8 nom_reg = cx24123_readreg(state, 0x0e);
	u8 auto_reg = cx24123_readreg(state, 0x10);

	switch (inversion) {
	case INVERSION_OFF:
		dprintk("inversion off\n");
		cx24123_writereg(state, 0x0e, nom_reg & ~0x80);
		cx24123_writereg(state, 0x10, auto_reg | 0x80);
		break;
	case INVERSION_ON:
		dprintk("inversion on\n");
		cx24123_writereg(state, 0x0e, nom_reg | 0x80);
		cx24123_writereg(state, 0x10, auto_reg | 0x80);
		break;
	case INVERSION_AUTO:
		dprintk("inversion auto\n");
		cx24123_writereg(state, 0x10, auto_reg & ~0x80);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}