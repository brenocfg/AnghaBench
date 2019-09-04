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
typedef  int /*<<< orphan*/  u8 ;
struct mtip_port {int dummy; } ;
struct host_to_dev_fis {int type; int opts; int features; int sect_count; int lba_mid; int lba_hi; int /*<<< orphan*/  device; int /*<<< orphan*/  command; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CMD_SMART ; 
 int /*<<< orphan*/  ATA_DEVICE_OBS ; 
 int /*<<< orphan*/  ATA_SECT_SIZE ; 
 int /*<<< orphan*/  memset (struct host_to_dev_fis*,int /*<<< orphan*/ ,int) ; 
 int mtip_exec_internal_command (struct mtip_port*,struct host_to_dev_fis*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtip_get_smart_data(struct mtip_port *port, u8 *buffer,
					dma_addr_t buffer_dma)
{
	struct host_to_dev_fis fis;

	memset(&fis, 0, sizeof(struct host_to_dev_fis));
	fis.type	= 0x27;
	fis.opts	= 1 << 7;
	fis.command	= ATA_CMD_SMART;
	fis.features	= 0xD0;
	fis.sect_count	= 1;
	fis.lba_mid	= 0x4F;
	fis.lba_hi	= 0xC2;
	fis.device	= ATA_DEVICE_OBS;

	return mtip_exec_internal_command(port,
					&fis,
					5,
					buffer_dma,
					ATA_SECT_SIZE,
					0,
					15000);
}