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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ath10k_sdio_hif_diag_read (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_hif_diag_read32(struct ath10k *ar, u32 address,
				       u32 *value)
{
	__le32 *val;
	int ret;

	val = kzalloc(sizeof(*val), GFP_KERNEL);
	if (!val)
		return -ENOMEM;

	ret = ath10k_sdio_hif_diag_read(ar, address, val, sizeof(*val));
	if (ret)
		goto out;

	*value = __le32_to_cpu(*val);

out:
	kfree(val);

	return ret;
}