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
struct drxd_state {int dummy; } ;

/* Variables and functions */
 int DRXD_MAX_RETRIES ; 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_RA_RAM_CMD__A ; 

__attribute__((used)) static int SC_WaitForReady(struct drxd_state *state)
{
	int i;

	for (i = 0; i < DRXD_MAX_RETRIES; i += 1) {
		int status = Read16(state, SC_RA_RAM_CMD__A, NULL, 0);
		if (status == 0)
			return status;
	}
	return -1;
}