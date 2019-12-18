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
struct scsi_cmnd {int flags; TYPE_1__* request; } ;
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int SCMD_TAGGED ; 
 int /*<<< orphan*/  SIMPLE_QUEUE_TAG ; 

int spi_populate_tag_msg(unsigned char *msg, struct scsi_cmnd *cmd)
{
        if (cmd->flags & SCMD_TAGGED) {
		*msg++ = SIMPLE_QUEUE_TAG;
        	*msg++ = cmd->request->tag;
        	return 2;
	}

	return 0;
}