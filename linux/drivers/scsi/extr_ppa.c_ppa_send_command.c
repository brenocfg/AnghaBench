#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int cmd_len; int /*<<< orphan*/ * cmnd; TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ ppa_struct ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_2__* ppa_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppa_out (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  w_ctr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ppa_send_command(struct scsi_cmnd *cmd)
{
	ppa_struct *dev = ppa_dev(cmd->device->host);
	int k;

	w_ctr(dev->base, 0x0c);

	for (k = 0; k < cmd->cmd_len; k++)
		if (!ppa_out(dev, &cmd->cmnd[k], 1))
			return 0;
	return 1;
}