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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_qspi_cmd {scalar_t__ addr_width; int /*<<< orphan*/  framemode; scalar_t__ tx_data; } ;
struct spi_nor {int read_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_ADMODE_1 ; 
 int /*<<< orphan*/  CCR_DMODE_1 ; 
 int /*<<< orphan*/  CCR_DMODE_2 ; 
 int /*<<< orphan*/  CCR_DMODE_4 ; 
 int /*<<< orphan*/  CCR_IMODE_1 ; 
#define  SNOR_PROTO_1_1_1 130 
#define  SNOR_PROTO_1_1_2 129 
#define  SNOR_PROTO_1_1_4 128 

__attribute__((used)) static void stm32_qspi_set_framemode(struct spi_nor *nor,
				     struct stm32_qspi_cmd *cmd, bool read)
{
	u32 dmode = CCR_DMODE_1;

	cmd->framemode = CCR_IMODE_1;

	if (read) {
		switch (nor->read_proto) {
		default:
		case SNOR_PROTO_1_1_1:
			dmode = CCR_DMODE_1;
			break;
		case SNOR_PROTO_1_1_2:
			dmode = CCR_DMODE_2;
			break;
		case SNOR_PROTO_1_1_4:
			dmode = CCR_DMODE_4;
			break;
		}
	}

	cmd->framemode |= cmd->tx_data ? dmode : 0;
	cmd->framemode |= cmd->addr_width ? CCR_ADMODE_1 : 0;
}