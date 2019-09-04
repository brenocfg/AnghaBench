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
typedef  int uint32_t ;
struct ipu {int dummy; } ;
typedef  enum ipu_channel { ____Placeholder_ipu_channel } ipu_channel ;

/* Variables and functions */
#define  IDMAC_IC_0 131 
#define  IDMAC_IC_7 130 
#define  IDMAC_SDC_0 129 
#define  IDMAC_SDC_1 128 
 int /*<<< orphan*/  IPU_TASKS_STAT ; 
 int TASK_STAT_IDLE ; 
 int TSTAT_CSI2MEM_MASK ; 
 int TSTAT_CSI2MEM_OFFSET ; 
 int idmac_read_ipureg (struct ipu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t ipu_channel_status(struct ipu *ipu, enum ipu_channel channel)
{
	uint32_t stat = TASK_STAT_IDLE;
	uint32_t task_stat_reg = idmac_read_ipureg(ipu, IPU_TASKS_STAT);

	switch (channel) {
	case IDMAC_IC_7:
		stat = (task_stat_reg & TSTAT_CSI2MEM_MASK) >>
			TSTAT_CSI2MEM_OFFSET;
		break;
	case IDMAC_IC_0:
	case IDMAC_SDC_0:
	case IDMAC_SDC_1:
	default:
		break;
	}
	return stat;
}