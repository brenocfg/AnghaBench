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
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_mcdi_async_completer ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int _efx_mcdi_rpc_async (struct efx_nic*,unsigned int,int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/ *,unsigned long,int) ; 

int
efx_mcdi_rpc_async(struct efx_nic *efx, unsigned int cmd,
		   const efx_dword_t *inbuf, size_t inlen, size_t outlen,
		   efx_mcdi_async_completer *complete, unsigned long cookie)
{
	return _efx_mcdi_rpc_async(efx, cmd, inbuf, inlen, outlen, complete,
				   cookie, false);
}