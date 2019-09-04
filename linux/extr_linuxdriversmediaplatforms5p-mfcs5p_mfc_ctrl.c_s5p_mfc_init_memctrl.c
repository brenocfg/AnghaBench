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
struct s5p_mfc_dev {int /*<<< orphan*/ * dma_base; } ;

/* Variables and functions */
 size_t BANK_L_CTX ; 
 size_t BANK_R_CTX ; 
 scalar_t__ IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  S5P_FIMV_MC_DRAMBASE_ADR_A ; 
 int /*<<< orphan*/  S5P_FIMV_MC_DRAMBASE_ADR_B ; 
 int /*<<< orphan*/  S5P_FIMV_RISC_BASE_ADDRESS_V6 ; 
 int /*<<< orphan*/  mfc_debug (int,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void s5p_mfc_init_memctrl(struct s5p_mfc_dev *dev)
{
	if (IS_MFCV6_PLUS(dev)) {
		mfc_write(dev, dev->dma_base[BANK_L_CTX],
			  S5P_FIMV_RISC_BASE_ADDRESS_V6);
		mfc_debug(2, "Base Address : %pad\n",
			  &dev->dma_base[BANK_L_CTX]);
	} else {
		mfc_write(dev, dev->dma_base[BANK_L_CTX],
			  S5P_FIMV_MC_DRAMBASE_ADR_A);
		mfc_write(dev, dev->dma_base[BANK_R_CTX],
			  S5P_FIMV_MC_DRAMBASE_ADR_B);
		mfc_debug(2, "Bank1: %pad, Bank2: %pad\n",
			  &dev->dma_base[BANK_L_CTX],
			  &dev->dma_base[BANK_R_CTX]);
	}
}