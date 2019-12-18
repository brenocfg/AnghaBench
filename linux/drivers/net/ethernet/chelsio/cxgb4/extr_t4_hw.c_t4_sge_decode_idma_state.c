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
typedef  char const* u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
 unsigned int CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
#define  CHELSIO_T4 133 
#define  CHELSIO_T5 132 
#define  CHELSIO_T6 131 
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,...) ; 
#define  SGE_DEBUG_DATA_HIGH_INDEX_10_A 130 
#define  SGE_DEBUG_DATA_LOW_INDEX_2_A 129 
#define  SGE_DEBUG_DATA_LOW_INDEX_3_A 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,char const* const) ; 

void t4_sge_decode_idma_state(struct adapter *adapter, int state)
{
	static const char * const t4_decode[] = {
		"IDMA_IDLE",
		"IDMA_PUSH_MORE_CPL_FIFO",
		"IDMA_PUSH_CPL_MSG_HEADER_TO_FIFO",
		"Not used",
		"IDMA_PHYSADDR_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PAYLOAD_FIRST",
		"IDMA_PHYSADDR_SEND_PAYLOAD",
		"IDMA_SEND_FIFO_TO_IMSG",
		"IDMA_FL_REQ_DATA_FL_PREP",
		"IDMA_FL_REQ_DATA_FL",
		"IDMA_FL_DROP",
		"IDMA_FL_H_REQ_HEADER_FL",
		"IDMA_FL_H_SEND_PCIEHDR",
		"IDMA_FL_H_PUSH_CPL_FIFO",
		"IDMA_FL_H_SEND_CPL",
		"IDMA_FL_H_SEND_IP_HDR_FIRST",
		"IDMA_FL_H_SEND_IP_HDR",
		"IDMA_FL_H_REQ_NEXT_HEADER_FL",
		"IDMA_FL_H_SEND_NEXT_PCIEHDR",
		"IDMA_FL_H_SEND_IP_HDR_PADDING",
		"IDMA_FL_D_SEND_PCIEHDR",
		"IDMA_FL_D_SEND_CPL_AND_IP_HDR",
		"IDMA_FL_D_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_PCIEHDR",
		"IDMA_FL_PUSH_CPL_FIFO",
		"IDMA_FL_SEND_CPL",
		"IDMA_FL_SEND_PAYLOAD_FIRST",
		"IDMA_FL_SEND_PAYLOAD",
		"IDMA_FL_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_NEXT_PCIEHDR",
		"IDMA_FL_SEND_PADDING",
		"IDMA_FL_SEND_COMPLETION_TO_IMSG",
		"IDMA_FL_SEND_FIFO_TO_IMSG",
		"IDMA_FL_REQ_DATAFL_DONE",
		"IDMA_FL_REQ_HEADERFL_DONE",
	};
	static const char * const t5_decode[] = {
		"IDMA_IDLE",
		"IDMA_ALMOST_IDLE",
		"IDMA_PUSH_MORE_CPL_FIFO",
		"IDMA_PUSH_CPL_MSG_HEADER_TO_FIFO",
		"IDMA_SGEFLRFLUSH_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PAYLOAD_FIRST",
		"IDMA_PHYSADDR_SEND_PAYLOAD",
		"IDMA_SEND_FIFO_TO_IMSG",
		"IDMA_FL_REQ_DATA_FL",
		"IDMA_FL_DROP",
		"IDMA_FL_DROP_SEND_INC",
		"IDMA_FL_H_REQ_HEADER_FL",
		"IDMA_FL_H_SEND_PCIEHDR",
		"IDMA_FL_H_PUSH_CPL_FIFO",
		"IDMA_FL_H_SEND_CPL",
		"IDMA_FL_H_SEND_IP_HDR_FIRST",
		"IDMA_FL_H_SEND_IP_HDR",
		"IDMA_FL_H_REQ_NEXT_HEADER_FL",
		"IDMA_FL_H_SEND_NEXT_PCIEHDR",
		"IDMA_FL_H_SEND_IP_HDR_PADDING",
		"IDMA_FL_D_SEND_PCIEHDR",
		"IDMA_FL_D_SEND_CPL_AND_IP_HDR",
		"IDMA_FL_D_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_PCIEHDR",
		"IDMA_FL_PUSH_CPL_FIFO",
		"IDMA_FL_SEND_CPL",
		"IDMA_FL_SEND_PAYLOAD_FIRST",
		"IDMA_FL_SEND_PAYLOAD",
		"IDMA_FL_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_NEXT_PCIEHDR",
		"IDMA_FL_SEND_PADDING",
		"IDMA_FL_SEND_COMPLETION_TO_IMSG",
	};
	static const char * const t6_decode[] = {
		"IDMA_IDLE",
		"IDMA_PUSH_MORE_CPL_FIFO",
		"IDMA_PUSH_CPL_MSG_HEADER_TO_FIFO",
		"IDMA_SGEFLRFLUSH_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PCIEHDR",
		"IDMA_PHYSADDR_SEND_PAYLOAD_FIRST",
		"IDMA_PHYSADDR_SEND_PAYLOAD",
		"IDMA_FL_REQ_DATA_FL",
		"IDMA_FL_DROP",
		"IDMA_FL_DROP_SEND_INC",
		"IDMA_FL_H_REQ_HEADER_FL",
		"IDMA_FL_H_SEND_PCIEHDR",
		"IDMA_FL_H_PUSH_CPL_FIFO",
		"IDMA_FL_H_SEND_CPL",
		"IDMA_FL_H_SEND_IP_HDR_FIRST",
		"IDMA_FL_H_SEND_IP_HDR",
		"IDMA_FL_H_REQ_NEXT_HEADER_FL",
		"IDMA_FL_H_SEND_NEXT_PCIEHDR",
		"IDMA_FL_H_SEND_IP_HDR_PADDING",
		"IDMA_FL_D_SEND_PCIEHDR",
		"IDMA_FL_D_SEND_CPL_AND_IP_HDR",
		"IDMA_FL_D_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_PCIEHDR",
		"IDMA_FL_PUSH_CPL_FIFO",
		"IDMA_FL_SEND_CPL",
		"IDMA_FL_SEND_PAYLOAD_FIRST",
		"IDMA_FL_SEND_PAYLOAD",
		"IDMA_FL_REQ_NEXT_DATA_FL",
		"IDMA_FL_SEND_NEXT_PCIEHDR",
		"IDMA_FL_SEND_PADDING",
		"IDMA_FL_SEND_COMPLETION_TO_IMSG",
	};
	static const u32 sge_regs[] = {
		SGE_DEBUG_DATA_LOW_INDEX_2_A,
		SGE_DEBUG_DATA_LOW_INDEX_3_A,
		SGE_DEBUG_DATA_HIGH_INDEX_10_A,
	};
	const char **sge_idma_decode;
	int sge_idma_decode_nstates;
	int i;
	unsigned int chip_version = CHELSIO_CHIP_VERSION(adapter->params.chip);

	/* Select the right set of decode strings to dump depending on the
	 * adapter chip type.
	 */
	switch (chip_version) {
	case CHELSIO_T4:
		sge_idma_decode = (const char **)t4_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t4_decode);
		break;

	case CHELSIO_T5:
		sge_idma_decode = (const char **)t5_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t5_decode);
		break;

	case CHELSIO_T6:
		sge_idma_decode = (const char **)t6_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t6_decode);
		break;

	default:
		dev_err(adapter->pdev_dev,
			"Unsupported chip version %d\n", chip_version);
		return;
	}

	if (is_t4(adapter->params.chip)) {
		sge_idma_decode = (const char **)t4_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t4_decode);
	} else {
		sge_idma_decode = (const char **)t5_decode;
		sge_idma_decode_nstates = ARRAY_SIZE(t5_decode);
	}

	if (state < sge_idma_decode_nstates)
		CH_WARN(adapter, "idma state %s\n", sge_idma_decode[state]);
	else
		CH_WARN(adapter, "idma state %d unknown\n", state);

	for (i = 0; i < ARRAY_SIZE(sge_regs); i++)
		CH_WARN(adapter, "SGE register %#x value %#x\n",
			sge_regs[i], t4_read_reg(adapter, sge_regs[i]));
}