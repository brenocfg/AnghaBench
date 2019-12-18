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
struct iss_resizer_device {int dummy; } ;
struct iss_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RZA ; 
 int /*<<< orphan*/  DMA_RZB ; 
 int /*<<< orphan*/  DMA_STA ; 
 int DWN_EN ; 
 int EN ; 
 int /*<<< orphan*/  FRACDIV ; 
 int /*<<< orphan*/  GCK_MMR ; 
 int /*<<< orphan*/  GCK_SDR ; 
 int H_DIF ; 
 int H_LPF ; 
 int H_PHS ; 
 int H_TYP ; 
 int /*<<< orphan*/  IN_FIFO_CTRL ; 
 int /*<<< orphan*/  IRQ_RZA ; 
 int /*<<< orphan*/  IRQ_RZB ; 
 int I_HPS ; 
 int I_VPS ; 
 int MODE ; 
 int O_HSZ ; 
 int O_VSZ ; 
 int /*<<< orphan*/  RSZ_PRINT_REGISTER (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RZA_PRINT_REGISTER (struct iss_device*,int) ; 
 int SDR_C_BAD_H ; 
 int SDR_C_BAD_L ; 
 int SDR_C_OFT ; 
 int SDR_C_PTR_E ; 
 int SDR_C_PTR_S ; 
 int SDR_C_SAD_H ; 
 int SDR_C_SAD_L ; 
 int SDR_Y_BAD_H ; 
 int SDR_Y_BAD_L ; 
 int SDR_Y_OFT ; 
 int SDR_Y_PTR_E ; 
 int SDR_Y_PTR_S ; 
 int SDR_Y_SAD_H ; 
 int SDR_Y_SAD_L ; 
 int /*<<< orphan*/  SEQ ; 
 int /*<<< orphan*/  SRC_EN ; 
 int /*<<< orphan*/  SRC_FMT0 ; 
 int /*<<< orphan*/  SRC_FMT1 ; 
 int /*<<< orphan*/  SRC_HPS ; 
 int /*<<< orphan*/  SRC_HSZ ; 
 int /*<<< orphan*/  SRC_MODE ; 
 int /*<<< orphan*/  SRC_VPS ; 
 int /*<<< orphan*/  SRC_VSZ ; 
 int /*<<< orphan*/  SYSCONFIG ; 
 int V_DIF ; 
 int V_LPF ; 
 int V_PHS_C ; 
 int V_PHS_Y ; 
 int V_TYP ; 
 int /*<<< orphan*/  YUV_C_MAX ; 
 int /*<<< orphan*/  YUV_C_MIN ; 
 int /*<<< orphan*/  YUV_Y_MAX ; 
 int /*<<< orphan*/  YUV_Y_MIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct iss_device* to_iss_device (struct iss_resizer_device*) ; 

__attribute__((used)) static void resizer_print_status(struct iss_resizer_device *resizer)
{
	struct iss_device *iss = to_iss_device(resizer);

	dev_dbg(iss->dev, "-------------RESIZER Register dump-------------\n");

	RSZ_PRINT_REGISTER(iss, SYSCONFIG);
	RSZ_PRINT_REGISTER(iss, IN_FIFO_CTRL);
	RSZ_PRINT_REGISTER(iss, FRACDIV);
	RSZ_PRINT_REGISTER(iss, SRC_EN);
	RSZ_PRINT_REGISTER(iss, SRC_MODE);
	RSZ_PRINT_REGISTER(iss, SRC_FMT0);
	RSZ_PRINT_REGISTER(iss, SRC_FMT1);
	RSZ_PRINT_REGISTER(iss, SRC_VPS);
	RSZ_PRINT_REGISTER(iss, SRC_VSZ);
	RSZ_PRINT_REGISTER(iss, SRC_HPS);
	RSZ_PRINT_REGISTER(iss, SRC_HSZ);
	RSZ_PRINT_REGISTER(iss, DMA_RZA);
	RSZ_PRINT_REGISTER(iss, DMA_RZB);
	RSZ_PRINT_REGISTER(iss, DMA_STA);
	RSZ_PRINT_REGISTER(iss, GCK_MMR);
	RSZ_PRINT_REGISTER(iss, GCK_SDR);
	RSZ_PRINT_REGISTER(iss, IRQ_RZA);
	RSZ_PRINT_REGISTER(iss, IRQ_RZB);
	RSZ_PRINT_REGISTER(iss, YUV_Y_MIN);
	RSZ_PRINT_REGISTER(iss, YUV_Y_MAX);
	RSZ_PRINT_REGISTER(iss, YUV_C_MIN);
	RSZ_PRINT_REGISTER(iss, YUV_C_MAX);
	RSZ_PRINT_REGISTER(iss, SEQ);

	RZA_PRINT_REGISTER(iss, EN);
	RZA_PRINT_REGISTER(iss, MODE);
	RZA_PRINT_REGISTER(iss, 420);
	RZA_PRINT_REGISTER(iss, I_VPS);
	RZA_PRINT_REGISTER(iss, I_HPS);
	RZA_PRINT_REGISTER(iss, O_VSZ);
	RZA_PRINT_REGISTER(iss, O_HSZ);
	RZA_PRINT_REGISTER(iss, V_PHS_Y);
	RZA_PRINT_REGISTER(iss, V_PHS_C);
	RZA_PRINT_REGISTER(iss, V_DIF);
	RZA_PRINT_REGISTER(iss, V_TYP);
	RZA_PRINT_REGISTER(iss, V_LPF);
	RZA_PRINT_REGISTER(iss, H_PHS);
	RZA_PRINT_REGISTER(iss, H_DIF);
	RZA_PRINT_REGISTER(iss, H_TYP);
	RZA_PRINT_REGISTER(iss, H_LPF);
	RZA_PRINT_REGISTER(iss, DWN_EN);
	RZA_PRINT_REGISTER(iss, SDR_Y_BAD_H);
	RZA_PRINT_REGISTER(iss, SDR_Y_BAD_L);
	RZA_PRINT_REGISTER(iss, SDR_Y_SAD_H);
	RZA_PRINT_REGISTER(iss, SDR_Y_SAD_L);
	RZA_PRINT_REGISTER(iss, SDR_Y_OFT);
	RZA_PRINT_REGISTER(iss, SDR_Y_PTR_S);
	RZA_PRINT_REGISTER(iss, SDR_Y_PTR_E);
	RZA_PRINT_REGISTER(iss, SDR_C_BAD_H);
	RZA_PRINT_REGISTER(iss, SDR_C_BAD_L);
	RZA_PRINT_REGISTER(iss, SDR_C_SAD_H);
	RZA_PRINT_REGISTER(iss, SDR_C_SAD_L);
	RZA_PRINT_REGISTER(iss, SDR_C_OFT);
	RZA_PRINT_REGISTER(iss, SDR_C_PTR_S);
	RZA_PRINT_REGISTER(iss, SDR_C_PTR_E);

	dev_dbg(iss->dev, "-----------------------------------------------\n");
}