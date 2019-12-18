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
struct TYPE_2__ {int /*<<< orphan*/ * rx_indir_table; } ;
struct efx_nic {TYPE_1__ rss_context; } ;
typedef  int /*<<< orphan*/  efx_dword_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  EFX_POPULATE_DWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRF_BZ_IT_QUEUE ; 
 scalar_t__ FR_BZ_RX_INDIRECTION_TBL ; 
 size_t FR_BZ_RX_INDIRECTION_TBL_ROWS ; 
 size_t FR_BZ_RX_INDIRECTION_TBL_STEP ; 
 int /*<<< orphan*/  efx_writed (struct efx_nic*,int /*<<< orphan*/ *,scalar_t__) ; 

void efx_farch_rx_push_indir_table(struct efx_nic *efx)
{
	size_t i = 0;
	efx_dword_t dword;

	BUILD_BUG_ON(ARRAY_SIZE(efx->rss_context.rx_indir_table) !=
		     FR_BZ_RX_INDIRECTION_TBL_ROWS);

	for (i = 0; i < FR_BZ_RX_INDIRECTION_TBL_ROWS; i++) {
		EFX_POPULATE_DWORD_1(dword, FRF_BZ_IT_QUEUE,
				     efx->rss_context.rx_indir_table[i]);
		efx_writed(efx, &dword,
			   FR_BZ_RX_INDIRECTION_TBL +
			   FR_BZ_RX_INDIRECTION_TBL_STEP * i);
	}
}