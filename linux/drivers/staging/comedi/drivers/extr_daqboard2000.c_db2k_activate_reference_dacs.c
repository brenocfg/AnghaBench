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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int DB2K_DAC_STATUS_REF_BUSY ; 
 int DB2K_REF_DACS_SELECT_NEG_REF ; 
 int DB2K_REF_DACS_SELECT_POS_REF ; 
 int DB2K_REF_DACS_SET ; 
 scalar_t__ DB2K_REG_DAC_STATUS ; 
 scalar_t__ DB2K_REG_REF_DACS ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void db2k_activate_reference_dacs(struct comedi_device *dev)
{
	unsigned int val;
	int timeout;

	/*  Set the + reference dac value in the FPGA */
	writew(DB2K_REF_DACS_SET | DB2K_REF_DACS_SELECT_POS_REF,
	       dev->mmio + DB2K_REG_REF_DACS);
	for (timeout = 0; timeout < 20; timeout++) {
		val = readw(dev->mmio + DB2K_REG_DAC_STATUS);
		if ((val & DB2K_DAC_STATUS_REF_BUSY) == 0)
			break;
		udelay(2);
	}

	/*  Set the - reference dac value in the FPGA */
	writew(DB2K_REF_DACS_SET | DB2K_REF_DACS_SELECT_NEG_REF,
	       dev->mmio + DB2K_REG_REF_DACS);
	for (timeout = 0; timeout < 20; timeout++) {
		val = readw(dev->mmio + DB2K_REG_DAC_STATUS);
		if ((val & DB2K_DAC_STATUS_REF_BUSY) == 0)
			break;
		udelay(2);
	}
}