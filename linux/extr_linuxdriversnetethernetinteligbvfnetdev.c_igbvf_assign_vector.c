#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {TYPE_2__* tx_ring; TYPE_1__* rx_ring; struct e1000_hw hw; } ;
struct TYPE_4__ {void* eims_value; } ;
struct TYPE_3__ {void* eims_value; } ;

/* Variables and functions */
 void* BIT (int) ; 
 int E1000_IVAR_VALID ; 
 int IGBVF_NO_QUEUE ; 
 int /*<<< orphan*/  IVAR0 ; 
 int array_er32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  array_ew32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void igbvf_assign_vector(struct igbvf_adapter *adapter, int rx_queue,
				int tx_queue, int msix_vector)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 ivar, index;

	/* 82576 uses a table-based method for assigning vectors.
	 * Each queue has a single entry in the table to which we write
	 * a vector number along with a "valid" bit.  Sadly, the layout
	 * of the table is somewhat counterintuitive.
	 */
	if (rx_queue > IGBVF_NO_QUEUE) {
		index = (rx_queue >> 1);
		ivar = array_er32(IVAR0, index);
		if (rx_queue & 0x1) {
			/* vector goes into third byte of register */
			ivar = ivar & 0xFF00FFFF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 16;
		} else {
			/* vector goes into low byte of register */
			ivar = ivar & 0xFFFFFF00;
			ivar |= msix_vector | E1000_IVAR_VALID;
		}
		adapter->rx_ring[rx_queue].eims_value = BIT(msix_vector);
		array_ew32(IVAR0, index, ivar);
	}
	if (tx_queue > IGBVF_NO_QUEUE) {
		index = (tx_queue >> 1);
		ivar = array_er32(IVAR0, index);
		if (tx_queue & 0x1) {
			/* vector goes into high byte of register */
			ivar = ivar & 0x00FFFFFF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 24;
		} else {
			/* vector goes into second byte of register */
			ivar = ivar & 0xFFFF00FF;
			ivar |= (msix_vector | E1000_IVAR_VALID) << 8;
		}
		adapter->tx_ring[tx_queue].eims_value = BIT(msix_vector);
		array_ew32(IVAR0, index, ivar);
	}
}