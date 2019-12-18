#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ms_offset; } ;
typedef  TYPE_1__ Scsi_CD ;

/* Variables and functions */
 int /*<<< orphan*/  CD_FRAMESIZE_RAW1 ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SR_GFP_DMA (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int) ; 
 int /*<<< orphan*/  sr_printk (int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 scalar_t__ sr_read_sector (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  xa_test ; 

int sr_is_xa(Scsi_CD *cd)
{
	unsigned char *raw_sector;
	int is_xa;

	if (!xa_test)
		return 0;

	raw_sector = kmalloc(2048, GFP_KERNEL | SR_GFP_DMA(cd));
	if (!raw_sector)
		return -ENOMEM;
	if (0 == sr_read_sector(cd, cd->ms_offset + 16,
				CD_FRAMESIZE_RAW1, raw_sector)) {
		is_xa = (raw_sector[3] == 0x02) ? 1 : 0;
	} else {
		/* read a raw sector failed for some reason. */
		is_xa = -1;
	}
	kfree(raw_sector);
#ifdef DEBUG
	sr_printk(KERN_INFO, cd, "sr_is_xa: %d\n", is_xa);
#endif
	return is_xa;
}