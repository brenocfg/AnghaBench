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
struct s5h1420_state {int dummy; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int s5h1420_readreg (struct s5h1420_state*,int) ; 

__attribute__((used)) static enum fe_status s5h1420_get_status_bits(struct s5h1420_state *state)
{
	u8 val;
	enum fe_status status = 0;

	val = s5h1420_readreg(state, 0x14);
	if (val & 0x02)
		status |=  FE_HAS_SIGNAL;
	if (val & 0x01)
		status |=  FE_HAS_CARRIER;
	val = s5h1420_readreg(state, 0x36);
	if (val & 0x01)
		status |=  FE_HAS_VITERBI;
	if (val & 0x20)
		status |=  FE_HAS_SYNC;
	if (status == (FE_HAS_SIGNAL|FE_HAS_CARRIER|FE_HAS_VITERBI|FE_HAS_SYNC))
		status |=  FE_HAS_LOCK;

	return status;
}