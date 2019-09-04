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
typedef  int u8 ;
struct fsl_qspi {int /*<<< orphan*/  dev; TYPE_1__* nor; } ;
struct TYPE_2__ {int erase_opcode; } ;

/* Variables and functions */
 int EINVAL ; 
 int SEQID_BRWR ; 
 int SEQID_CHIP_ERASE ; 
 int SEQID_EN4B ; 
 int SEQID_PP ; 
 int SEQID_RDCR ; 
 int SEQID_RDID ; 
 int SEQID_RDSR ; 
 int SEQID_READ ; 
 int SEQID_SE ; 
 int SEQID_WRDI ; 
 int SEQID_WREN ; 
 int SEQID_WRSR ; 
#define  SPINOR_OP_BRWR 140 
#define  SPINOR_OP_CHIP_ERASE 139 
#define  SPINOR_OP_EN4B 138 
#define  SPINOR_OP_PP 137 
#define  SPINOR_OP_RDCR 136 
#define  SPINOR_OP_RDID 135 
#define  SPINOR_OP_RDSR 134 
#define  SPINOR_OP_READ_1_1_4 133 
#define  SPINOR_OP_READ_1_1_4_4B 132 
#define  SPINOR_OP_SE 131 
#define  SPINOR_OP_WRDI 130 
#define  SPINOR_OP_WREN 129 
#define  SPINOR_OP_WRSR 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int fsl_qspi_get_seqid(struct fsl_qspi *q, u8 cmd)
{
	switch (cmd) {
	case SPINOR_OP_READ_1_1_4:
	case SPINOR_OP_READ_1_1_4_4B:
		return SEQID_READ;
	case SPINOR_OP_WREN:
		return SEQID_WREN;
	case SPINOR_OP_WRDI:
		return SEQID_WRDI;
	case SPINOR_OP_RDSR:
		return SEQID_RDSR;
	case SPINOR_OP_SE:
		return SEQID_SE;
	case SPINOR_OP_CHIP_ERASE:
		return SEQID_CHIP_ERASE;
	case SPINOR_OP_PP:
		return SEQID_PP;
	case SPINOR_OP_RDID:
		return SEQID_RDID;
	case SPINOR_OP_WRSR:
		return SEQID_WRSR;
	case SPINOR_OP_RDCR:
		return SEQID_RDCR;
	case SPINOR_OP_EN4B:
		return SEQID_EN4B;
	case SPINOR_OP_BRWR:
		return SEQID_BRWR;
	default:
		if (cmd == q->nor[0].erase_opcode)
			return SEQID_SE;
		dev_err(q->dev, "Unsupported cmd 0x%.2x\n", cmd);
		break;
	}
	return -EINVAL;
}