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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ath10k_pci_diag_read_mem (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_pci_diag_read32(struct ath10k *ar, u32 address, u32 *value)
{
	__le32 val = 0;
	int ret;

	ret = ath10k_pci_diag_read_mem(ar, address, &val, sizeof(val));
	*value = __le32_to_cpu(val);

	return ret;
}