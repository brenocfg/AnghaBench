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
struct hwicap_drvdata {TYPE_1__* config; } ;
struct TYPE_2__ {int (* set_configuration ) (struct hwicap_drvdata*,int*,int) ;int (* get_status ) (struct hwicap_drvdata*) ;int (* get_configuration ) (struct hwicap_drvdata*,int*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int XHI_DUMMY_PACKET ; 
 int XHI_NOOP_PACKET ; 
 int XHI_SR_DALIGN_MASK ; 
 int XHI_SYNC_PACKET ; 
 int hwicap_type_1_read (int) ; 
 int stub1 (struct hwicap_drvdata*,int*,int) ; 
 int stub2 (struct hwicap_drvdata*) ; 
 int stub3 (struct hwicap_drvdata*,int*,int) ; 
 int stub4 (struct hwicap_drvdata*,int*,int) ; 

__attribute__((used)) static int hwicap_get_configuration_register(struct hwicap_drvdata *drvdata,
		u32 reg, u32 *reg_data)
{
	int status;
	u32 buffer[6];
	u32 index = 0;

	/*
	 * Create the data to be written to the ICAP.
	 */
	buffer[index++] = XHI_DUMMY_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_SYNC_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;

	/*
	 * Write the data to the FIFO and initiate the transfer of data present
	 * in the FIFO to the ICAP device.
	 */
	status = drvdata->config->set_configuration(drvdata,
						    &buffer[0], index);
	if (status)
		return status;

	/* If the syncword was not found, then we need to start over. */
	status = drvdata->config->get_status(drvdata);
	if ((status & XHI_SR_DALIGN_MASK) != XHI_SR_DALIGN_MASK)
		return -EIO;

	index = 0;
	buffer[index++] = hwicap_type_1_read(reg) | 1;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;

	/*
	 * Write the data to the FIFO and intiate the transfer of data present
	 * in the FIFO to the ICAP device.
	 */
	status = drvdata->config->set_configuration(drvdata,
			&buffer[0], index);
	if (status)
		return status;

	/*
	 * Read the configuration register
	 */
	status = drvdata->config->get_configuration(drvdata, reg_data, 1);
	if (status)
		return status;

	return 0;
}