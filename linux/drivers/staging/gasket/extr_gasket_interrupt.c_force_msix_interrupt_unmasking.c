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
typedef  scalar_t__ ulong ;
typedef  int u32 ;
struct gasket_dev {TYPE_1__* interrupt_data; } ;
struct TYPE_2__ {int num_configured; int /*<<< orphan*/  interrupt_bar_index; } ;

/* Variables and functions */
 scalar_t__ APEX_BAR2_REG_KERNEL_HIB_MSIX_TABLE ; 
 scalar_t__ MSIX_MASK_BIT_OFFSET ; 
 int MSIX_VECTOR_SIZE ; 
 int gasket_dev_read_32 (struct gasket_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gasket_dev_write_32 (struct gasket_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void force_msix_interrupt_unmasking(struct gasket_dev *gasket_dev)
{
	int i;
#define MSIX_VECTOR_SIZE 16
#define MSIX_MASK_BIT_OFFSET 12
#define APEX_BAR2_REG_KERNEL_HIB_MSIX_TABLE 0x46800
	for (i = 0; i < gasket_dev->interrupt_data->num_configured; i++) {
		/* Check if the MSIX vector is unmasked */
		ulong location = APEX_BAR2_REG_KERNEL_HIB_MSIX_TABLE +
				 MSIX_MASK_BIT_OFFSET + i * MSIX_VECTOR_SIZE;
		u32 mask =
			gasket_dev_read_32(gasket_dev,
					   gasket_dev->interrupt_data->interrupt_bar_index,
					   location);
		if (!(mask & 1))
			continue;
		/* Unmask the msix vector (clear 32 bits) */
		gasket_dev_write_32(gasket_dev, 0,
				    gasket_dev->interrupt_data->interrupt_bar_index,
				    location);
	}
#undef MSIX_VECTOR_SIZE
#undef MSIX_MASK_BIT_OFFSET
#undef APEX_BAR2_REG_KERNEL_HIB_MSIX_TABLE
}