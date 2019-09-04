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
typedef  int u16 ;
struct drxd_state {int m_EcOcRegOcModeLop; int m_EcOcRegSncSncLvl; } ;

/* Variables and functions */
 int EC_OC_REG_COMM_EXEC_CTL_ACTIVE ; 
 int EC_OC_REG_COMM_EXEC_CTL_HOLD ; 
 int /*<<< orphan*/  EC_OC_REG_COMM_EXEC__A ; 
 int /*<<< orphan*/  EC_OC_REG_COMM_INT_STA__A ; 
 int /*<<< orphan*/  EC_OC_REG_DTO_INC_HIP__A ; 
 int /*<<< orphan*/  EC_OC_REG_DTO_INC_LOP__A ; 
 int /*<<< orphan*/  EC_OC_REG_OCR_MPG_UOS__A ; 
 int EC_OC_REG_OCR_MPG_UOS__M ; 
 int EC_OC_REG_OC_MODE_LOP_DTO_CTR_SRC_STATIC ; 
 int EC_OC_REG_OC_MODE_LOP_DTO_CTR_SRC__M ; 
 int EC_OC_REG_OC_MODE_LOP_PAR_ENA_ENABLE ; 
 int EC_OC_REG_OC_MODE_LOP_PAR_ENA__M ; 
 int /*<<< orphan*/  EC_OC_REG_OC_MODE_LOP__A ; 
 int /*<<< orphan*/  EC_OC_REG_RCN_MAP_HIP__A ; 
 int /*<<< orphan*/  EC_OC_REG_RCN_MAP_LOP__A ; 
 int EC_OC_REG_SNC_ISC_LVL_OSC__M ; 
 int /*<<< orphan*/  EC_OC_REG_SNC_ISC_LVL__A ; 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int StopOC(struct drxd_state *state)
{
	int status = 0;
	u16 ocSyncLvl = 0;
	u16 ocModeLop = state->m_EcOcRegOcModeLop;
	u16 dtoIncLop = 0;
	u16 dtoIncHip = 0;

	do {
		/* Store output configuration */
		status = Read16(state, EC_OC_REG_SNC_ISC_LVL__A, &ocSyncLvl, 0);
		if (status < 0)
			break;
		/* CHK_ERROR(Read16(EC_OC_REG_OC_MODE_LOP__A, &ocModeLop)); */
		state->m_EcOcRegSncSncLvl = ocSyncLvl;
		/* m_EcOcRegOcModeLop = ocModeLop; */

		/* Flush FIFO (byte-boundary) at fixed rate */
		status = Read16(state, EC_OC_REG_RCN_MAP_LOP__A, &dtoIncLop, 0);
		if (status < 0)
			break;
		status = Read16(state, EC_OC_REG_RCN_MAP_HIP__A, &dtoIncHip, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_DTO_INC_LOP__A, dtoIncLop, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_DTO_INC_HIP__A, dtoIncHip, 0);
		if (status < 0)
			break;
		ocModeLop &= ~(EC_OC_REG_OC_MODE_LOP_DTO_CTR_SRC__M);
		ocModeLop |= EC_OC_REG_OC_MODE_LOP_DTO_CTR_SRC_STATIC;
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, ocModeLop, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_HOLD, 0);
		if (status < 0)
			break;

		msleep(1);
		/* Output pins to '0' */
		status = Write16(state, EC_OC_REG_OCR_MPG_UOS__A, EC_OC_REG_OCR_MPG_UOS__M, 0);
		if (status < 0)
			break;

		/* Force the OC out of sync */
		ocSyncLvl &= ~(EC_OC_REG_SNC_ISC_LVL_OSC__M);
		status = Write16(state, EC_OC_REG_SNC_ISC_LVL__A, ocSyncLvl, 0);
		if (status < 0)
			break;
		ocModeLop &= ~(EC_OC_REG_OC_MODE_LOP_PAR_ENA__M);
		ocModeLop |= EC_OC_REG_OC_MODE_LOP_PAR_ENA_ENABLE;
		ocModeLop |= 0x2;	/* Magically-out-of-sync */
		status = Write16(state, EC_OC_REG_OC_MODE_LOP__A, ocModeLop, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_COMM_INT_STA__A, 0x0, 0);
		if (status < 0)
			break;
		status = Write16(state, EC_OC_REG_COMM_EXEC__A, EC_OC_REG_COMM_EXEC_CTL_ACTIVE, 0);
		if (status < 0)
			break;
	} while (0);

	return status;
}