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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_WINDOW_DATA_ADDRESS ; 
 int /*<<< orphan*/  MBOX_WINDOW_WRITE_ADDR_ADDRESS ; 
 int ath10k_sdio_write (struct ath10k*,int /*<<< orphan*/ ,void const*,int) ; 
 int ath10k_sdio_write32 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 

__attribute__((used)) static int ath10k_sdio_hif_diag_write_mem(struct ath10k *ar, u32 address,
					  const void *data, int nbytes)
{
	int ret;

	/* set write data */
	ret = ath10k_sdio_write(ar, MBOX_WINDOW_DATA_ADDRESS, data, nbytes);
	if (ret) {
		ath10k_warn(ar,
			    "failed to write 0x%p to mbox window data address: %d\n",
			    data, ret);
		return ret;
	}

	/* set window register, which starts the write cycle */
	ret = ath10k_sdio_write32(ar, MBOX_WINDOW_WRITE_ADDR_ADDRESS, address);
	if (ret) {
		ath10k_warn(ar, "failed to set mbox window write address: %d", ret);
		return ret;
	}

	return 0;
}