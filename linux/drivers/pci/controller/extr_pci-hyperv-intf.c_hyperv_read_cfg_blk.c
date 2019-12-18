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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int (* read_block ) (struct pci_dev*,void*,unsigned int,unsigned int,unsigned int*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_1__ hvpci_block_ops ; 
 int stub1 (struct pci_dev*,void*,unsigned int,unsigned int,unsigned int*) ; 

int hyperv_read_cfg_blk(struct pci_dev *dev, void *buf, unsigned int buf_len,
			unsigned int block_id, unsigned int *bytes_returned)
{
	if (!hvpci_block_ops.read_block)
		return -EOPNOTSUPP;

	return hvpci_block_ops.read_block(dev, buf, buf_len, block_id,
					  bytes_returned);
}