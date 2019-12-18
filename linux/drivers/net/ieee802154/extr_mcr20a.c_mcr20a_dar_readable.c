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
struct device {int dummy; } ;

/* Variables and functions */
#define  DAR_CCA1_ED_FNL 138 
#define  DAR_EVENT_TMR_LSB 137 
#define  DAR_EVENT_TMR_MSB 136 
#define  DAR_EVENT_TMR_USB 135 
#define  DAR_LQI_VALUE 134 
#define  DAR_RSSI_CCA_CONT 133 
#define  DAR_RX_FRM_LEN 132 
#define  DAR_SEQ_STATE 131 
#define  DAR_TIMESTAMP_LSB 130 
#define  DAR_TIMESTAMP_MSB 129 
#define  DAR_TIMESTAMP_USB 128 
 int mcr20a_dar_writeable (struct device*,unsigned int) ; 

__attribute__((used)) static bool
mcr20a_dar_readable(struct device *dev, unsigned int reg)
{
	bool rc;

	/* all writeable are also readable */
	rc = mcr20a_dar_writeable(dev, reg);
	if (rc)
		return rc;

	/* readonly regs */
	switch (reg) {
	case DAR_RX_FRM_LEN:
	case DAR_CCA1_ED_FNL:
	case DAR_EVENT_TMR_LSB:
	case DAR_EVENT_TMR_MSB:
	case DAR_EVENT_TMR_USB:
	case DAR_TIMESTAMP_LSB:
	case DAR_TIMESTAMP_MSB:
	case DAR_TIMESTAMP_USB:
	case DAR_SEQ_STATE:
	case DAR_LQI_VALUE:
	case DAR_RSSI_CCA_CONT:
		return true;
	default:
		return false;
	}
}