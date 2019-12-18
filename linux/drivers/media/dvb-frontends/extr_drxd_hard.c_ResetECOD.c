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
struct drxd_state {int /*<<< orphan*/  m_ResetECRAM; scalar_t__ type_A; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_EC_OD_REG_SYNC__A ; 
 int /*<<< orphan*/  EC_OD_REG_COMM_EXEC__A ; 
 int /*<<< orphan*/  EC_OD_REG_SYNC__A ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int WriteTable (struct drxd_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ResetECOD(struct drxd_state *state)
{
	int status = 0;

	if (state->type_A)
		status = Write16(state, EC_OD_REG_SYNC__A, 0x0664, 0);
	else
		status = Write16(state, B_EC_OD_REG_SYNC__A, 0x0664, 0);

	if (!(status < 0))
		status = WriteTable(state, state->m_ResetECRAM);
	if (!(status < 0))
		status = Write16(state, EC_OD_REG_COMM_EXEC__A, 0x0001, 0);
	return status;
}