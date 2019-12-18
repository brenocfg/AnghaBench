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
typedef  void* u8 ;
struct TYPE_2__ {void** cdb; int /*<<< orphan*/  flags_hi; int /*<<< orphan*/  request_type; } ;
struct ipr_ioarcb {TYPE_1__ cmd_pkt; int /*<<< orphan*/  res_handle; } ;
struct ipr_cmnd {struct ipr_ioarcb ioarcb; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPR_FLAGS_HI_WRITE_NOT_READ ; 
 int /*<<< orphan*/  IPR_IOADL_FLAGS_WRITE_LAST ; 
 int /*<<< orphan*/  IPR_RQTYPE_SCSICDB ; 
 void* MODE_SELECT ; 
 int /*<<< orphan*/  ipr_init_ioadl (struct ipr_cmnd*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_build_mode_select(struct ipr_cmnd *ipr_cmd,
				  __be32 res_handle, u8 parm,
				  dma_addr_t dma_addr, u8 xfer_len)
{
	struct ipr_ioarcb *ioarcb = &ipr_cmd->ioarcb;

	ioarcb->res_handle = res_handle;
	ioarcb->cmd_pkt.request_type = IPR_RQTYPE_SCSICDB;
	ioarcb->cmd_pkt.flags_hi |= IPR_FLAGS_HI_WRITE_NOT_READ;
	ioarcb->cmd_pkt.cdb[0] = MODE_SELECT;
	ioarcb->cmd_pkt.cdb[1] = parm;
	ioarcb->cmd_pkt.cdb[4] = xfer_len;

	ipr_init_ioadl(ipr_cmd, dma_addr, xfer_len, IPR_IOADL_FLAGS_WRITE_LAST);
}