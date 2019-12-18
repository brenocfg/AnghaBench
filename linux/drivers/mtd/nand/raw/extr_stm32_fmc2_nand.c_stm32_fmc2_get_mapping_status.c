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
typedef  int u16 ;
struct stm32_fmc2_nfc {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ FMC2_CSQEMSR ; 
 int FMC2_CSQEMSR_SEM ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u16 stm32_fmc2_get_mapping_status(struct stm32_fmc2_nfc *fmc2)
{
	u32 csqemsr = readl_relaxed(fmc2->io_base + FMC2_CSQEMSR);

	return csqemsr & FMC2_CSQEMSR_SEM;
}