#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  enum pmcmsptwi_xfer_result { ____Placeholder_pmcmsptwi_xfer_result } pmcmsptwi_xfer_result ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MSP_TWI_INT_STS_BUSY ; 
 int MSP_TWI_INT_STS_DATA_COLLISION ; 
 int MSP_TWI_INT_STS_LOST_ARBITRATION ; 
 int MSP_TWI_INT_STS_NO_RESPONSE ; 
 int MSP_TWI_XFER_BUSY ; 
 int MSP_TWI_XFER_DATA_COLLISION ; 
 int MSP_TWI_XFER_LOST_ARBITRATION ; 
 int MSP_TWI_XFER_NO_RESPONSE ; 
 int MSP_TWI_XFER_OK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ pmcmsptwi_adapter ; 

__attribute__((used)) static enum pmcmsptwi_xfer_result pmcmsptwi_get_result(u32 reg)
{
	if (reg & MSP_TWI_INT_STS_LOST_ARBITRATION) {
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: Lost arbitration\n");
		return MSP_TWI_XFER_LOST_ARBITRATION;
	} else if (reg & MSP_TWI_INT_STS_NO_RESPONSE) {
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: No response\n");
		return MSP_TWI_XFER_NO_RESPONSE;
	} else if (reg & MSP_TWI_INT_STS_DATA_COLLISION) {
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: Data collision\n");
		return MSP_TWI_XFER_DATA_COLLISION;
	} else if (reg & MSP_TWI_INT_STS_BUSY) {
		dev_dbg(&pmcmsptwi_adapter.dev,
			"Result: Bus busy\n");
		return MSP_TWI_XFER_BUSY;
	}

	dev_dbg(&pmcmsptwi_adapter.dev, "Result: Operation succeeded\n");
	return MSP_TWI_XFER_OK;
}