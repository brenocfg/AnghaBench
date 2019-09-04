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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int RTSX_PHASE_MAX ; 
 scalar_t__ test_phase_bit (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sd_get_phase_len(u32 phase_map, unsigned int start_bit)
{
	int i;

	for (i = 0; i < RTSX_PHASE_MAX; i++) {
		if (test_phase_bit(phase_map, start_bit + i) == 0)
			return i;
	}
	return RTSX_PHASE_MAX;
}