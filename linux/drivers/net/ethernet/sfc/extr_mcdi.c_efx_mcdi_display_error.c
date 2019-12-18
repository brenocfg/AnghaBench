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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  ERR_ARG ; 
 int /*<<< orphan*/  ERR_CODE ; 
 int MCDI_DWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MC_CMD_ERR_ARG_OFST ; 
 int MC_CMD_ERR_CODE_OFST ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_cond_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,unsigned int,size_t,int,int,int) ; 

void efx_mcdi_display_error(struct efx_nic *efx, unsigned cmd,
			    size_t inlen, efx_dword_t *outbuf,
			    size_t outlen, int rc)
{
	int code = 0, err_arg = 0;

	if (outlen >= MC_CMD_ERR_CODE_OFST + 4)
		code = MCDI_DWORD(outbuf, ERR_CODE);
	if (outlen >= MC_CMD_ERR_ARG_OFST + 4)
		err_arg = MCDI_DWORD(outbuf, ERR_ARG);
	netif_cond_dbg(efx, hw, efx->net_dev, rc == -EPERM, err,
		       "MC command 0x%x inlen %zu failed rc=%d (raw=%d) arg=%d\n",
		       cmd, inlen, rc, code, err_arg);
}