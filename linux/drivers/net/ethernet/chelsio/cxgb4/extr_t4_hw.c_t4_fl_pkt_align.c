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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 unsigned int INGPACKBOUNDARY_16B_X ; 
 unsigned int INGPACKBOUNDARY_G (int /*<<< orphan*/ ) ; 
 unsigned int INGPACKBOUNDARY_SHIFT_X ; 
 unsigned int INGPADBOUNDARY_G (int /*<<< orphan*/ ) ; 
 unsigned int INGPADBOUNDARY_SHIFT_X ; 
 int /*<<< orphan*/  SGE_CONTROL2_A ; 
 int /*<<< orphan*/  SGE_CONTROL_A ; 
 unsigned int T6_INGPADBOUNDARY_SHIFT_X ; 
 int /*<<< orphan*/  is_t4 (int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

int t4_fl_pkt_align(struct adapter *adap)
{
	u32 sge_control, sge_control2;
	unsigned int ingpadboundary, ingpackboundary, fl_align, ingpad_shift;

	sge_control = t4_read_reg(adap, SGE_CONTROL_A);

	/* T4 uses a single control field to specify both the PCIe Padding and
	 * Packing Boundary.  T5 introduced the ability to specify these
	 * separately.  The actual Ingress Packet Data alignment boundary
	 * within Packed Buffer Mode is the maximum of these two
	 * specifications.  (Note that it makes no real practical sense to
	 * have the Padding Boundary be larger than the Packing Boundary but you
	 * could set the chip up that way and, in fact, legacy T4 code would
	 * end doing this because it would initialize the Padding Boundary and
	 * leave the Packing Boundary initialized to 0 (16 bytes).)
	 * Padding Boundary values in T6 starts from 8B,
	 * where as it is 32B for T4 and T5.
	 */
	if (CHELSIO_CHIP_VERSION(adap->params.chip) <= CHELSIO_T5)
		ingpad_shift = INGPADBOUNDARY_SHIFT_X;
	else
		ingpad_shift = T6_INGPADBOUNDARY_SHIFT_X;

	ingpadboundary = 1 << (INGPADBOUNDARY_G(sge_control) + ingpad_shift);

	fl_align = ingpadboundary;
	if (!is_t4(adap->params.chip)) {
		/* T5 has a weird interpretation of one of the PCIe Packing
		 * Boundary values.  No idea why ...
		 */
		sge_control2 = t4_read_reg(adap, SGE_CONTROL2_A);
		ingpackboundary = INGPACKBOUNDARY_G(sge_control2);
		if (ingpackboundary == INGPACKBOUNDARY_16B_X)
			ingpackboundary = 16;
		else
			ingpackboundary = 1 << (ingpackboundary +
						INGPACKBOUNDARY_SHIFT_X);

		fl_align = max(ingpadboundary, ingpackboundary);
	}
	return fl_align;
}