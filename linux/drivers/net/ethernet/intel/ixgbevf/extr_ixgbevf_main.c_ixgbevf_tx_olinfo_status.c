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
struct TYPE_2__ {int /*<<< orphan*/  olinfo_status; } ;
union ixgbe_adv_tx_desc {TYPE_1__ read; } ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 unsigned int IXGBE_ADVTXD_CC ; 
 unsigned int IXGBE_ADVTXD_IDX_SHIFT ; 
 unsigned int IXGBE_ADVTXD_PAYLEN_SHIFT ; 
 unsigned int IXGBE_ADVTXD_POPTS_IPSEC ; 
 unsigned int IXGBE_ADVTXD_POPTS_IXSM ; 
 unsigned int IXGBE_ADVTXD_POPTS_TXSM ; 
 int IXGBE_TX_FLAGS_CSUM ; 
 int IXGBE_TX_FLAGS_IPSEC ; 
 int IXGBE_TX_FLAGS_IPV4 ; 
 int IXGBE_TX_FLAGS_TSO ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static void ixgbevf_tx_olinfo_status(union ixgbe_adv_tx_desc *tx_desc,
				     u32 tx_flags, unsigned int paylen)
{
	__le32 olinfo_status = cpu_to_le32(paylen << IXGBE_ADVTXD_PAYLEN_SHIFT);

	/* enable L4 checksum for TSO and TX checksum offload */
	if (tx_flags & IXGBE_TX_FLAGS_CSUM)
		olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_POPTS_TXSM);

	/* enble IPv4 checksum for TSO */
	if (tx_flags & IXGBE_TX_FLAGS_IPV4)
		olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_POPTS_IXSM);

	/* enable IPsec */
	if (tx_flags & IXGBE_TX_FLAGS_IPSEC)
		olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_POPTS_IPSEC);

	/* use index 1 context for TSO/FSO/FCOE/IPSEC */
	if (tx_flags & (IXGBE_TX_FLAGS_TSO | IXGBE_TX_FLAGS_IPSEC))
		olinfo_status |= cpu_to_le32(1u << IXGBE_ADVTXD_IDX_SHIFT);

	/* Check Context must be set if Tx switch is enabled, which it
	 * always is for case where virtual functions are running
	 */
	olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_CC);

	tx_desc->read.olinfo_status = olinfo_status;
}