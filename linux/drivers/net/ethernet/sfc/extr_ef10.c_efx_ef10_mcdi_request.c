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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct TYPE_2__ {scalar_t__ dma_addr; int /*<<< orphan*/ * addr; } ;
struct efx_ef10_nic_data {TYPE_1__ mcdi_buf; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  ER_DZ_MC_DB_HWRD ; 
 int /*<<< orphan*/  ER_DZ_MC_DB_LWRD ; 
 int /*<<< orphan*/  _efx_writed (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void efx_ef10_mcdi_request(struct efx_nic *efx,
				  const efx_dword_t *hdr, size_t hdr_len,
				  const efx_dword_t *sdu, size_t sdu_len)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	u8 *pdu = nic_data->mcdi_buf.addr;

	memcpy(pdu, hdr, hdr_len);
	memcpy(pdu + hdr_len, sdu, sdu_len);
	wmb();

	/* The hardware provides 'low' and 'high' (doorbell) registers
	 * for passing the 64-bit address of an MCDI request to
	 * firmware.  However the dwords are swapped by firmware.  The
	 * least significant bits of the doorbell are then 0 for all
	 * MCDI requests due to alignment.
	 */
	_efx_writed(efx, cpu_to_le32((u64)nic_data->mcdi_buf.dma_addr >> 32),
		    ER_DZ_MC_DB_LWRD);
	_efx_writed(efx, cpu_to_le32((u32)nic_data->mcdi_buf.dma_addr),
		    ER_DZ_MC_DB_HWRD);
}