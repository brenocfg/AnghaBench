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
struct s5h1420_state {int dummy; } ;
typedef  enum fe_spectral_inversion { ____Placeholder_fe_spectral_inversion } fe_spectral_inversion ;

/* Variables and functions */
 int INVERSION_OFF ; 
 int INVERSION_ON ; 
 int s5h1420_readreg (struct s5h1420_state*,int) ; 

__attribute__((used)) static enum fe_spectral_inversion
s5h1420_getinversion(struct s5h1420_state *state)
{
	if (s5h1420_readreg(state, 0x32) & 0x08)
		return INVERSION_ON;

	return INVERSION_OFF;
}