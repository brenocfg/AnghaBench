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
typedef  size_t uint16_t ;
struct xfer_info_t {int /*<<< orphan*/  state; int /*<<< orphan*/  EraseCount; int /*<<< orphan*/  Offset; } ;
struct erase_info {int len; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  mtd; } ;
struct TYPE_5__ {int EraseUnitSize; } ;
struct TYPE_7__ {TYPE_2__ mbd; TYPE_1__ header; struct xfer_info_t* XferInfo; } ;
typedef  TYPE_3__ partition_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XFER_ERASED ; 
 int /*<<< orphan*/  XFER_ERASING ; 
 int /*<<< orphan*/  XFER_FAILED ; 
 int /*<<< orphan*/  kfree (struct erase_info*) ; 
 struct erase_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_erase (int /*<<< orphan*/ ,struct erase_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 

__attribute__((used)) static int erase_xfer(partition_t *part,
		      uint16_t xfernum)
{
    int ret;
    struct xfer_info_t *xfer;
    struct erase_info *erase;

    xfer = &part->XferInfo[xfernum];
    pr_debug("ftl_cs: erasing xfer unit at 0x%x\n", xfer->Offset);
    xfer->state = XFER_ERASING;

    /* Is there a free erase slot? Always in MTD. */


    erase=kmalloc(sizeof(struct erase_info), GFP_KERNEL);
    if (!erase)
            return -ENOMEM;

    erase->addr = xfer->Offset;
    erase->len = 1 << part->header.EraseUnitSize;

    ret = mtd_erase(part->mbd.mtd, erase);
    if (!ret) {
	xfer->state = XFER_ERASED;
	xfer->EraseCount++;
    } else {
	xfer->state = XFER_FAILED;
	pr_notice("ftl_cs: erase failed: err = %d\n", ret);
    }

    kfree(erase);

    return ret;
}