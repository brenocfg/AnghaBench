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
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int _efx_mcdi_rpc_finish (struct efx_nic*,unsigned int,size_t,int /*<<< orphan*/ *,size_t,size_t*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int efx_mcdi_rpc_finish(struct efx_nic *efx, unsigned cmd, size_t inlen,
			efx_dword_t *outbuf, size_t outlen,
			size_t *outlen_actual)
{
	return _efx_mcdi_rpc_finish(efx, cmd, inlen, outbuf, outlen,
				    outlen_actual, false, NULL, NULL);
}