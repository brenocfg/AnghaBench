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
struct drxd_state {int /*<<< orphan*/  m_EcOcRegOcModeLop; int /*<<< orphan*/  m_EcOcRegSncSncLvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_OC_REG_COMM_EXEC_CTL_ACTIVE ; 
 int /*<<< orphan*/  EC_OC_REG_COMM_EXEC_CTL_HOLD ; 
 int /*<<< orphan*/  EC_OC_REG_COMM_EXEC__A ; 
 int /*<<< orphan*/  EC_OC_REG_OCR_MPG_UOS_INIT ; 
 int /*<<< orphan*/  EC_OC_REG_OCR_MPG_UOS__A ; 
 int /*<<< orphan*/  EC_OC_REG_OC_MODE_LOP__A ; 
 int /*<<< orphan*/  EC_OC_REG_SNC_ISC_LVL__A ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int StartOC(struct drxd_state *state)
{
	int status = 0;

	do {
		/* Stop OC */
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_HOLD, 0);
		if (status < 0)
			break;

		/* Restore output configuration */
		status = Write16(state, EC_OC_REG_SNC_ISC_LVL__A, state->m_EcOcRegSncSncLvl, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, state->m_EcOcRegOcModeLop, 0);
		if (status < 0)
			break;

		/* Output pins active again */
		status = Write16(state, EC_OC_REG_OCR_MPG_UOS__A, EC_OC_REG_OCR_MPG_UOS_INIT, 0);
		if (status < 0)
			break;

		/* Start OC */
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_ACTIVE, 0);
		if (status < 0)
			break;
	} while (0);
	return status;
}