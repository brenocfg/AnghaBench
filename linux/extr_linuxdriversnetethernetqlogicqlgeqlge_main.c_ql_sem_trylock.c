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
typedef  int u32 ;
struct ql_adapter {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SEM ; 
#define  SEM_FLASH_MASK 135 
 int SEM_FLASH_SHIFT ; 
#define  SEM_ICB_MASK 134 
 int SEM_ICB_SHIFT ; 
#define  SEM_MAC_ADDR_MASK 133 
 int SEM_MAC_ADDR_SHIFT ; 
#define  SEM_PROBE_MASK 132 
 int SEM_PROBE_SHIFT ; 
#define  SEM_PROC_REG_MASK 131 
 int SEM_PROC_REG_SHIFT ; 
#define  SEM_RT_IDX_MASK 130 
 int SEM_RT_IDX_SHIFT ; 
 int SEM_SET ; 
#define  SEM_XGMAC0_MASK 129 
 int SEM_XGMAC0_SHIFT ; 
#define  SEM_XGMAC1_MASK 128 
 int SEM_XGMAC1_SHIFT ; 
 int /*<<< orphan*/  netif_alert (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ql_sem_trylock(struct ql_adapter *qdev, u32 sem_mask)
{
	u32 sem_bits = 0;

	switch (sem_mask) {
	case SEM_XGMAC0_MASK:
		sem_bits = SEM_SET << SEM_XGMAC0_SHIFT;
		break;
	case SEM_XGMAC1_MASK:
		sem_bits = SEM_SET << SEM_XGMAC1_SHIFT;
		break;
	case SEM_ICB_MASK:
		sem_bits = SEM_SET << SEM_ICB_SHIFT;
		break;
	case SEM_MAC_ADDR_MASK:
		sem_bits = SEM_SET << SEM_MAC_ADDR_SHIFT;
		break;
	case SEM_FLASH_MASK:
		sem_bits = SEM_SET << SEM_FLASH_SHIFT;
		break;
	case SEM_PROBE_MASK:
		sem_bits = SEM_SET << SEM_PROBE_SHIFT;
		break;
	case SEM_RT_IDX_MASK:
		sem_bits = SEM_SET << SEM_RT_IDX_SHIFT;
		break;
	case SEM_PROC_REG_MASK:
		sem_bits = SEM_SET << SEM_PROC_REG_SHIFT;
		break;
	default:
		netif_alert(qdev, probe, qdev->ndev, "bad Semaphore mask!.\n");
		return -EINVAL;
	}

	ql_write32(qdev, SEM, sem_bits | sem_mask);
	return !(ql_read32(qdev, SEM) & sem_bits);
}