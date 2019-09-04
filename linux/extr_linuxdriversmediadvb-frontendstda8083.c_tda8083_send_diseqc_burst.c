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
struct tda8083_state {int dummy; } ;
typedef  enum fe_sec_mini_cmd { ____Placeholder_fe_sec_mini_cmd } fe_sec_mini_cmd ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_MINI_A 129 
#define  SEC_MINI_B 128 
 int /*<<< orphan*/  tda8083_wait_diseqc_fifo (struct tda8083_state*,int) ; 
 int /*<<< orphan*/  tda8083_writereg (struct tda8083_state*,int,int) ; 

__attribute__((used)) static int tda8083_send_diseqc_burst(struct tda8083_state *state,
				     enum fe_sec_mini_cmd burst)
{
	switch (burst) {
	case SEC_MINI_A:
		tda8083_writereg (state, 0x29, (5 << 2));  /* send burst A */
		break;
	case SEC_MINI_B:
		tda8083_writereg (state, 0x29, (7 << 2));  /* send B */
		break;
	default:
		return -EINVAL;
	}

	tda8083_wait_diseqc_fifo (state, 100);

	return 0;
}