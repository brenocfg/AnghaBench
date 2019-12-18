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
struct scsi_cmnd {TYPE_1__* device; } ;
struct fdomain {scalar_t__ chip; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ REG_FIFO ; 
 scalar_t__ REG_FIFO_COUNT ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outsw (scalar_t__,unsigned char*,size_t) ; 
 size_t scsi_bufflen (struct scsi_cmnd*) ; 
 size_t scsi_get_resid (struct scsi_cmnd*) ; 
 unsigned char* scsi_kmap_atomic_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*) ; 
 int /*<<< orphan*/  scsi_kunmap_atomic_sg (unsigned char*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,size_t) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 struct fdomain* shost_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ tmc18c30 ; 

__attribute__((used)) static void fdomain_write_data(struct scsi_cmnd *cmd)
{
	struct fdomain *fd = shost_priv(cmd->device->host);
	/* 8k FIFO for pre-tmc18c30 chips, 2k FIFO for tmc18c30 */
	int FIFO_Size = fd->chip == tmc18c30 ? 0x800 : 0x2000;
	unsigned char *virt, *ptr;
	size_t offset, len;

	while ((len = FIFO_Size - inw(fd->base + REG_FIFO_COUNT)) > 512) {
		offset = scsi_bufflen(cmd) - scsi_get_resid(cmd);
		if (len + offset > scsi_bufflen(cmd)) {
			len = scsi_bufflen(cmd) - offset;
			if (len == 0)
				break;
		}
		virt = scsi_kmap_atomic_sg(scsi_sglist(cmd), scsi_sg_count(cmd),
					   &offset, &len);
		ptr = virt + offset;
		if (len & 1)
			outb(*ptr++, fd->base + REG_FIFO);
		if (len > 1)
			outsw(fd->base + REG_FIFO, ptr, len >> 1);
		scsi_set_resid(cmd, scsi_get_resid(cmd) - len);
		scsi_kunmap_atomic_sg(virt);
	}
}