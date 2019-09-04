#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct xfer_info_t {int /*<<< orphan*/  state; scalar_t__ Offset; int /*<<< orphan*/  EraseCount; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  mtd; } ;
struct TYPE_7__ {int /*<<< orphan*/  BAMOffset; void* EraseCount; int /*<<< orphan*/  LogicalEUN; } ;
struct TYPE_6__ {int BlocksPerUnit; TYPE_1__ mbd; TYPE_3__ header; struct xfer_info_t* XferInfo; } ;
typedef  TYPE_2__ partition_t ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  header ;
typedef  TYPE_3__ erase_unit_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_CONTROL ; 
 int DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECTOR_SIZE ; 
 int /*<<< orphan*/  XFER_FAILED ; 
 int /*<<< orphan*/  XFER_PREPARED ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mtd_write (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 

__attribute__((used)) static int prepare_xfer(partition_t *part, int i)
{
    erase_unit_header_t header;
    struct xfer_info_t *xfer;
    int nbam, ret;
    uint32_t ctl;
    ssize_t retlen;
    loff_t offset;

    xfer = &part->XferInfo[i];
    xfer->state = XFER_FAILED;

    pr_debug("ftl_cs: preparing xfer unit at 0x%x\n", xfer->Offset);

    /* Write the transfer unit header */
    header = part->header;
    header.LogicalEUN = cpu_to_le16(0xffff);
    header.EraseCount = cpu_to_le32(xfer->EraseCount);

    ret = mtd_write(part->mbd.mtd, xfer->Offset, sizeof(header), &retlen,
                    (u_char *)&header);

    if (ret) {
	return ret;
    }

    /* Write the BAM stub */
    nbam = DIV_ROUND_UP(part->BlocksPerUnit * sizeof(uint32_t) +
			le32_to_cpu(part->header.BAMOffset), SECTOR_SIZE);

    offset = xfer->Offset + le32_to_cpu(part->header.BAMOffset);
    ctl = cpu_to_le32(BLOCK_CONTROL);

    for (i = 0; i < nbam; i++, offset += sizeof(uint32_t)) {

	ret = mtd_write(part->mbd.mtd, offset, sizeof(uint32_t), &retlen,
                        (u_char *)&ctl);

	if (ret)
	    return ret;
    }
    xfer->state = XFER_PREPARED;
    return 0;

}