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
typedef  int u32 ;
struct stv {int receive_mode; } ;

/* Variables and functions */
#define  RCVMODE_DVBS 129 
#define  RCVMODE_DVBS2 128 
 int get_bit_error_rate_s (struct stv*,int*,int*) ; 
 int get_bit_error_rate_s2 (struct stv*,int*,int*) ; 

__attribute__((used)) static int get_bit_error_rate(struct stv *state, u32 *bernumerator,
			      u32 *berdenominator)
{
	*bernumerator = 0;
	*berdenominator = 1;

	switch (state->receive_mode) {
	case RCVMODE_DVBS:
		return get_bit_error_rate_s(state,
					    bernumerator, berdenominator);
	case RCVMODE_DVBS2:
		return get_bit_error_rate_s2(state,
					     bernumerator, berdenominator);
	default:
		break;
	}
	return 0;
}