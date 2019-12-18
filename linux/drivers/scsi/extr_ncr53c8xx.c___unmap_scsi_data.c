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
struct scsi_cmnd {int __data_mapped; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 

__attribute__((used)) static void __unmap_scsi_data(struct device *dev, struct scsi_cmnd *cmd)
{
	switch(cmd->__data_mapped) {
	case 2:
		scsi_dma_unmap(cmd);
		break;
	}
	cmd->__data_mapped = 0;
}