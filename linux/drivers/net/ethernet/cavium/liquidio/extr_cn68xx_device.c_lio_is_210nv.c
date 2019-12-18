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
typedef  int u64 ;
struct octeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_MIO_QLM4_CFG ; 
 int CN6XXX_MIO_QLM_CFG_MASK ; 
 int lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lio_is_210nv(struct octeon_device *oct)
{
	u64 mio_qlm4_cfg = lio_pci_readq(oct, CN6XXX_MIO_QLM4_CFG);

	return ((mio_qlm4_cfg & CN6XXX_MIO_QLM_CFG_MASK) == 0);
}