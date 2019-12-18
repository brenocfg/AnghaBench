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

/* Variables and functions */
 int const FINGER_STATE_MASK ; 

__attribute__((used)) static inline u8 rmi_f11_parse_finger_state(const u8 *f_state, u8 n_finger)
{
	return (f_state[n_finger / 4] >> (2 * (n_finger % 4))) &
							FINGER_STATE_MASK;
}