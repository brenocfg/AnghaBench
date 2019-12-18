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
struct ni_gpct_device {int** regs; } ;
struct ni_gpct {unsigned int counter_index; unsigned int chip_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GI_BITS_TO_SRC (int /*<<< orphan*/ ) ; 
 int GI_SRC_SUBSEL ; 
 unsigned int NITIO_GATE2_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_INPUT_SEL_REG (unsigned int) ; 
 unsigned int NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_NEXT_TC_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_PFI_CLOCK_SRC_BITS (unsigned int) ; 
 unsigned int NI_GPCT_PXI10_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_RTSI_CLOCK_SRC_BITS (unsigned int) ; 
 unsigned int NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS ; 
 unsigned int NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS ; 
#define  NI_M_LOGIC_LOW_CLK 134 
 unsigned int NI_M_MAX_PFI_CHAN ; 
 unsigned int NI_M_MAX_RTSI_CHAN ; 
#define  NI_M_NEXT_GATE_CLK 133 
#define  NI_M_NEXT_TC_CLK 132 
 unsigned int NI_M_PFI_CLK (unsigned int) ; 
#define  NI_M_PXI10_CLK 131 
 unsigned int NI_M_RTSI_CLK (unsigned int) ; 
#define  NI_M_TIMEBASE_1_CLK 130 
#define  NI_M_TIMEBASE_2_CLK 129 
#define  NI_M_TIMEBASE_3_CLK 128 
 unsigned int ni_tio_clock_src_modifiers (struct ni_gpct const*) ; 
 int /*<<< orphan*/  ni_tio_get_soft_copy (struct ni_gpct const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_m_series_clock_src_select(const struct ni_gpct *counter,
					unsigned int *clk_src)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int chip = counter->chip_index;
	unsigned int second_gate_reg = NITIO_GATE2_REG(cidx);
	unsigned int clock_source = 0;
	unsigned int src;
	unsigned int i;

	src = GI_BITS_TO_SRC(ni_tio_get_soft_copy(counter,
						  NITIO_INPUT_SEL_REG(cidx)));

	switch (src) {
	case NI_M_TIMEBASE_1_CLK:
		clock_source = NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS;
		break;
	case NI_M_TIMEBASE_2_CLK:
		clock_source = NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS;
		break;
	case NI_M_TIMEBASE_3_CLK:
		if (counter_dev->regs[chip][second_gate_reg] & GI_SRC_SUBSEL)
			clock_source =
			    NI_GPCT_ANALOG_TRIGGER_OUT_CLOCK_SRC_BITS;
		else
			clock_source = NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS;
		break;
	case NI_M_LOGIC_LOW_CLK:
		clock_source = NI_GPCT_LOGIC_LOW_CLOCK_SRC_BITS;
		break;
	case NI_M_NEXT_GATE_CLK:
		if (counter_dev->regs[chip][second_gate_reg] & GI_SRC_SUBSEL)
			clock_source = NI_GPCT_PXI_STAR_TRIGGER_CLOCK_SRC_BITS;
		else
			clock_source = NI_GPCT_NEXT_GATE_CLOCK_SRC_BITS;
		break;
	case NI_M_PXI10_CLK:
		clock_source = NI_GPCT_PXI10_CLOCK_SRC_BITS;
		break;
	case NI_M_NEXT_TC_CLK:
		clock_source = NI_GPCT_NEXT_TC_CLOCK_SRC_BITS;
		break;
	default:
		for (i = 0; i <= NI_M_MAX_RTSI_CHAN; ++i) {
			if (src == NI_M_RTSI_CLK(i)) {
				clock_source = NI_GPCT_RTSI_CLOCK_SRC_BITS(i);
				break;
			}
		}
		if (i <= NI_M_MAX_RTSI_CHAN)
			break;
		for (i = 0; i <= NI_M_MAX_PFI_CHAN; ++i) {
			if (src == NI_M_PFI_CLK(i)) {
				clock_source = NI_GPCT_PFI_CLOCK_SRC_BITS(i);
				break;
			}
		}
		if (i <= NI_M_MAX_PFI_CHAN)
			break;
		return -EINVAL;
	}
	clock_source |= ni_tio_clock_src_modifiers(counter);
	*clk_src = clock_source;
	return 0;
}