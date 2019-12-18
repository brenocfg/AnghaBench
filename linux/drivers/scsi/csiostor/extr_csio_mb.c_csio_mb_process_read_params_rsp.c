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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct fw_params_cmd {int /*<<< orphan*/  retval_len16; TYPE_1__* param; } ;
struct csio_mb {scalar_t__ mb; } ;
struct csio_hw {int dummy; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int FW_CMD_RETVAL_G (int /*<<< orphan*/ ) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void
csio_mb_process_read_params_rsp(struct csio_hw *hw, struct csio_mb *mbp,
			   enum fw_retval *retval, unsigned int nparams,
			   u32 *val)
{
	struct fw_params_cmd *rsp = (struct fw_params_cmd *)(mbp->mb);
	uint32_t i;
	__be32 *p = &rsp->param[0].val;

	*retval = FW_CMD_RETVAL_G(ntohl(rsp->retval_len16));

	if (*retval == FW_SUCCESS)
		for (i = 0; i < nparams; i++, p += 2)
			*val++ = ntohl(*p);
}