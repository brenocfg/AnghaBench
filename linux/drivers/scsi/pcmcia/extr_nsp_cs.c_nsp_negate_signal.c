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
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {unsigned int io_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  SCSIBUSMON ; 
 unsigned char nsp_index_read (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_msg (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int nsp_negate_signal(struct scsi_cmnd *SCpnt, unsigned char mask,
			     char *str)
{
	unsigned int  base = SCpnt->device->host->io_port;
	unsigned char reg;
	int	      time_out;

	//nsp_dbg(NSP_DEBUG_INTR, "in");

	time_out = 100;

	do {
		reg = nsp_index_read(base, SCSIBUSMON);
		if (reg == 0xff) {
			break;
		}
	} while ((--time_out != 0) && (reg & mask) != 0);

	if (time_out == 0) {
		nsp_msg(KERN_DEBUG, " %s signal off timeout", str);
	}

	return 0;
}