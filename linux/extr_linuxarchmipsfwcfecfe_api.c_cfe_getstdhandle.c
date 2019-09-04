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
struct cfe_xiocb {scalar_t__ xiocb_status; int xiocb_handle; int xiocb_flags; scalar_t__ xiocb_psize; int /*<<< orphan*/  xiocb_fcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFE_CMD_DEV_GETHANDLE ; 
 int /*<<< orphan*/  cfe_iocb_dispatch (struct cfe_xiocb*) ; 

int cfe_getstdhandle(int flg)
{
	struct cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_GETHANDLE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = flg;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	if (xiocb.xiocb_status < 0)
		return xiocb.xiocb_status;
	return xiocb.xiocb_handle;
}