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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct drxd_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRXD_MAX_RETRIES ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_CMD__A ; 
 int /*<<< orphan*/  HI_RA_RAM_SRV_RES__A ; 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int HI_Command(struct drxd_state *state, u16 cmd, u16 * pResult)
{
	u32 nrRetries = 0;
	int status;

	status = Write16(state, HI_RA_RAM_SRV_CMD__A, cmd, 0);
	if (status < 0)
		return status;

	do {
		nrRetries += 1;
		if (nrRetries > DRXD_MAX_RETRIES) {
			status = -1;
			break;
		}
		status = Read16(state, HI_RA_RAM_SRV_CMD__A, NULL, 0);
	} while (status != 0);

	if (status >= 0)
		status = Read16(state, HI_RA_RAM_SRV_RES__A, pResult, 0);
	return status;
}