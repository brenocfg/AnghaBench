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
typedef  scalar_t__ u32 ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_mcdi_iface {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  const efx_dword_t ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  MCDI_STATE_RUNNING_SYNC ; 
 int /*<<< orphan*/  RESET_TYPE_MC_FAILURE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _efx_mcdi_rpc_finish (struct efx_nic*,unsigned int,size_t,int /*<<< orphan*/  const*,size_t,size_t*,int,scalar_t__*,int*) ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int efx_mcdi_proxy_wait (struct efx_nic*,scalar_t__,int) ; 
 int /*<<< orphan*/  efx_mcdi_release (struct efx_mcdi_iface*) ; 
 int efx_mcdi_rpc_start (struct efx_nic*,unsigned int,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  efx_mcdi_send_request (struct efx_nic*,unsigned int,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_cond_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int _efx_mcdi_rpc(struct efx_nic *efx, unsigned int cmd,
			 const efx_dword_t *inbuf, size_t inlen,
			 efx_dword_t *outbuf, size_t outlen,
			 size_t *outlen_actual, bool quiet, int *raw_rc)
{
	u32 proxy_handle = 0; /* Zero is an invalid proxy handle. */
	int rc;

	if (inbuf && inlen && (inbuf == outbuf)) {
		/* The input buffer can't be aliased with the output. */
		WARN_ON(1);
		return -EINVAL;
	}

	rc = efx_mcdi_rpc_start(efx, cmd, inbuf, inlen);
	if (rc)
		return rc;

	rc = _efx_mcdi_rpc_finish(efx, cmd, inlen, outbuf, outlen,
				  outlen_actual, quiet, &proxy_handle, raw_rc);

	if (proxy_handle) {
		/* Handle proxy authorisation. This allows approval of MCDI
		 * operations to be delegated to the admin function, allowing
		 * fine control over (eg) multicast subscriptions.
		 */
		struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

		netif_dbg(efx, hw, efx->net_dev,
			  "MCDI waiting for proxy auth %d\n",
			  proxy_handle);
		rc = efx_mcdi_proxy_wait(efx, proxy_handle, quiet);

		if (rc == 0) {
			netif_dbg(efx, hw, efx->net_dev,
				  "MCDI proxy retry %d\n", proxy_handle);

			/* We now retry the original request. */
			mcdi->state = MCDI_STATE_RUNNING_SYNC;
			efx_mcdi_send_request(efx, cmd, inbuf, inlen);

			rc = _efx_mcdi_rpc_finish(efx, cmd, inlen,
						  outbuf, outlen, outlen_actual,
						  quiet, NULL, raw_rc);
		} else {
			netif_cond_dbg(efx, hw, efx->net_dev, rc == -EPERM, err,
				       "MC command 0x%x failed after proxy auth rc=%d\n",
				       cmd, rc);

			if (rc == -EINTR || rc == -EIO)
				efx_schedule_reset(efx, RESET_TYPE_MC_FAILURE);
			efx_mcdi_release(mcdi);
		}
	}

	return rc;
}