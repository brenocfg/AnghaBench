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
typedef  int u64 ;
struct octeon_mgmt_cam_state {int* cam; int cam_index; unsigned long long cam_mask; } ;

/* Variables and functions */

__attribute__((used)) static void octeon_mgmt_cam_state_add(struct octeon_mgmt_cam_state *cs,
				      unsigned char *addr)
{
	int i;

	for (i = 0; i < 6; i++)
		cs->cam[i] |= (u64)addr[i] << (8 * (cs->cam_index));
	cs->cam_mask |= (1ULL << cs->cam_index);
	cs->cam_index++;
}