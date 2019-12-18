#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scif_epd_t ;
typedef  size_t off_t ;
struct TYPE_3__ {int /*<<< orphan*/  this_device; } ;
struct TYPE_4__ {TYPE_1__ mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOCAL_TO_REMOTE ; 
 size_t SCIF_MAX_UNALIGNED_BUF_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,size_t,size_t,int) ; 
 TYPE_2__ scif_info ; 
 int scif_rma_copy (int /*<<< orphan*/ ,size_t,int,size_t,size_t,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scif_unaligned (size_t,size_t) ; 

int scif_writeto(scif_epd_t epd, off_t loffset, size_t len,
		 off_t roffset, int flags)
{
	int err;

	dev_dbg(scif_info.mdev.this_device,
		"SCIFAPI writeto: ep %p loffset 0x%lx len 0x%lx roffset 0x%lx flags 0x%x\n",
		epd, loffset, len, roffset, flags);
	if (scif_unaligned(loffset, roffset)) {
		while (len > SCIF_MAX_UNALIGNED_BUF_SIZE) {
			err = scif_rma_copy(epd, loffset, 0x0,
					    SCIF_MAX_UNALIGNED_BUF_SIZE,
					    roffset, flags,
					    SCIF_LOCAL_TO_REMOTE, false);
			if (err)
				goto writeto_err;
			loffset += SCIF_MAX_UNALIGNED_BUF_SIZE;
			roffset += SCIF_MAX_UNALIGNED_BUF_SIZE;
			len -= SCIF_MAX_UNALIGNED_BUF_SIZE;
		}
	}
	err = scif_rma_copy(epd, loffset, 0x0, len,
			    roffset, flags, SCIF_LOCAL_TO_REMOTE, true);
writeto_err:
	return err;
}