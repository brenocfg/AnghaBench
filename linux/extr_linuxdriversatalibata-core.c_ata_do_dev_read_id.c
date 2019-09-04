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
typedef  int /*<<< orphan*/  u16 ;
struct ata_taskfile {int dummy; } ;
struct ata_device {int dummy; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int ATA_ID_WORDS ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 unsigned int ata_exec_internal (struct ata_device*,struct ata_taskfile*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

unsigned int ata_do_dev_read_id(struct ata_device *dev,
					struct ata_taskfile *tf, u16 *id)
{
	return ata_exec_internal(dev, tf, NULL, DMA_FROM_DEVICE,
				     id, sizeof(id[0]) * ATA_ID_WORDS, 0);
}