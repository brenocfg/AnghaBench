#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hwicap_drvdata {TYPE_1__* config; TYPE_2__* config_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  CMD; } ;
struct TYPE_3__ {int (* set_configuration ) (struct hwicap_drvdata*,int*,int) ;} ;

/* Variables and functions */
 int XHI_CMD_DESYNCH ; 
 int XHI_NOOP_PACKET ; 
 int hwicap_type_1_write (int /*<<< orphan*/ ) ; 
 int stub1 (struct hwicap_drvdata*,int*,int) ; 

__attribute__((used)) static int hwicap_command_desync(struct hwicap_drvdata *drvdata)
{
	u32 buffer[4];
	u32 index = 0;

	/*
	 * Create the data to be written to the ICAP.
	 */
	buffer[index++] = hwicap_type_1_write(drvdata->config_regs->CMD) | 1;
	buffer[index++] = XHI_CMD_DESYNCH;
	buffer[index++] = XHI_NOOP_PACKET;
	buffer[index++] = XHI_NOOP_PACKET;

	/*
	 * Write the data to the FIFO and intiate the transfer of data present
	 * in the FIFO to the ICAP device.
	 */
	return drvdata->config->set_configuration(drvdata,
			&buffer[0], index);
}