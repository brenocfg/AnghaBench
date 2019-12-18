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
 int ACK_COUNTER ; 
 int /*<<< orphan*/  POINTERCLR ; 
 int POINTER_CLEAR ; 
 int /*<<< orphan*/  TRANSFERCOUNT ; 
 unsigned int nsp_index_read (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nsp_fifo_count(struct scsi_cmnd *SCpnt)
{
	unsigned int base = SCpnt->device->host->io_port;
	unsigned int count;
	unsigned int l, m, h, dummy;

	nsp_index_write(base, POINTERCLR, POINTER_CLEAR | ACK_COUNTER);

	l     = nsp_index_read(base, TRANSFERCOUNT);
	m     = nsp_index_read(base, TRANSFERCOUNT);
	h     = nsp_index_read(base, TRANSFERCOUNT);
	dummy = nsp_index_read(base, TRANSFERCOUNT); /* required this! */

	count = (h << 16) | (m << 8) | (l << 0);

	//nsp_dbg(NSP_DEBUG_DATA_IO, "count=0x%x", count);

	return count;
}