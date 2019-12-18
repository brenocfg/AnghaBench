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

/* Variables and functions */
#define  BSPI_DONE 131 
#define  BSPI_ERR 130 
 int /*<<< orphan*/  BSPI_LR_INTERRUPTS_ALL ; 
 int /*<<< orphan*/  BSPI_LR_INTERRUPTS_ERROR ; 
 int /*<<< orphan*/  INTR_MSPI_DONE_MASK ; 
#define  MSPI_BSPI_DONE 129 
#define  MSPI_DONE 128 
 int /*<<< orphan*/  QSPI_INTERRUPTS_ALL ; 

__attribute__((used)) static inline u32 get_qspi_mask(int type)
{
	switch (type) {
	case MSPI_DONE:
		return INTR_MSPI_DONE_MASK;
	case BSPI_DONE:
		return BSPI_LR_INTERRUPTS_ALL;
	case MSPI_BSPI_DONE:
		return QSPI_INTERRUPTS_ALL;
	case BSPI_ERR:
		return BSPI_LR_INTERRUPTS_ERROR;
	}

	return 0;
}