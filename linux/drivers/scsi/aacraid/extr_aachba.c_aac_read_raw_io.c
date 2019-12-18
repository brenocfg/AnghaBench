#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sgentryraw {int dummy; } ;
struct sge_ieee1212 {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
struct fib {struct aac_dev* dev; } ;
struct aac_raw_io2 {int /*<<< orphan*/  sgeCnt; void* flags; void* cid; void* byteCount; void* blockHigh; void* blockLow; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;
struct aac_raw_io {TYPE_3__ sg; scalar_t__ bpComplete; scalar_t__ bpTotal; void* flags; void* cid; void* count; void** block; } ;
struct aac_fibhdr {int dummy; } ;
struct aac_dev {scalar_t__ comm_interface; int max_fib_size; TYPE_2__* fsa_dev; TYPE_1__* scsi_host_ptr; int /*<<< orphan*/  sync_mode; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_5__ {int block_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  sg_tablesize; } ;

/* Variables and functions */
 scalar_t__ AAC_COMM_MESSAGE_TYPE2 ; 
 scalar_t__ AAC_COMM_MESSAGE_TYPE3 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ContainerRawIo ; 
 int ContainerRawIo2 ; 
 int /*<<< orphan*/  FsaNormal ; 
 size_t RIO2_IO_TYPE_READ ; 
 size_t RIO_TYPE_READ ; 
 long aac_build_sgraw (struct scsi_cmnd*,TYPE_3__*) ; 
 long aac_build_sgraw2 (struct scsi_cmnd*,struct aac_raw_io2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 void* cpu_to_le16 (size_t) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ fib_data (struct fib*) ; 
 scalar_t__ io_callback ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct aac_raw_io2*,int /*<<< orphan*/ ,int) ; 
 size_t scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static int aac_read_raw_io(struct fib * fib, struct scsi_cmnd * cmd, u64 lba, u32 count)
{
	struct aac_dev *dev = fib->dev;
	u16 fibsize, command;
	long ret;

	aac_fib_init(fib);
	if ((dev->comm_interface == AAC_COMM_MESSAGE_TYPE2 ||
		dev->comm_interface == AAC_COMM_MESSAGE_TYPE3) &&
		!dev->sync_mode) {
		struct aac_raw_io2 *readcmd2;
		readcmd2 = (struct aac_raw_io2 *) fib_data(fib);
		memset(readcmd2, 0, sizeof(struct aac_raw_io2));
		readcmd2->blockLow = cpu_to_le32((u32)(lba&0xffffffff));
		readcmd2->blockHigh = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		readcmd2->byteCount = cpu_to_le32(count *
			dev->fsa_dev[scmd_id(cmd)].block_size);
		readcmd2->cid = cpu_to_le16(scmd_id(cmd));
		readcmd2->flags = cpu_to_le16(RIO2_IO_TYPE_READ);
		ret = aac_build_sgraw2(cmd, readcmd2,
				dev->scsi_host_ptr->sg_tablesize);
		if (ret < 0)
			return ret;
		command = ContainerRawIo2;
		fibsize = sizeof(struct aac_raw_io2) +
			((le32_to_cpu(readcmd2->sgeCnt)-1) * sizeof(struct sge_ieee1212));
	} else {
		struct aac_raw_io *readcmd;
		readcmd = (struct aac_raw_io *) fib_data(fib);
		readcmd->block[0] = cpu_to_le32((u32)(lba&0xffffffff));
		readcmd->block[1] = cpu_to_le32((u32)((lba&0xffffffff00000000LL)>>32));
		readcmd->count = cpu_to_le32(count *
			dev->fsa_dev[scmd_id(cmd)].block_size);
		readcmd->cid = cpu_to_le16(scmd_id(cmd));
		readcmd->flags = cpu_to_le16(RIO_TYPE_READ);
		readcmd->bpTotal = 0;
		readcmd->bpComplete = 0;
		ret = aac_build_sgraw(cmd, &readcmd->sg);
		if (ret < 0)
			return ret;
		command = ContainerRawIo;
		fibsize = sizeof(struct aac_raw_io) +
			((le32_to_cpu(readcmd->sg.count)-1) * sizeof(struct sgentryraw));
	}

	BUG_ON(fibsize > (fib->dev->max_fib_size - sizeof(struct aac_fibhdr)));
	/*
	 *	Now send the Fib to the adapter
	 */
	return aac_fib_send(command,
			  fib,
			  fibsize,
			  FsaNormal,
			  0, 1,
			  (fib_callback) io_callback,
			  (void *) cmd);
}