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
struct safexcel_crypto_priv {int base; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int EIP197_CLASSIFICATION_RAMS ; 
 int EIP197_PE (struct safexcel_crypto_priv*) ; 
 int EIP197_PE_ICE_RAM_CTRL (int) ; 
 int EIP197_PE_ICE_x_CTRL_CLR_ECC_CORR ; 
 int EIP197_PE_ICE_x_CTRL_CLR_ECC_NON_CORR ; 
 int EIP197_PE_ICE_x_CTRL_SW_RESET ; 
 int be32_to_cpu (int const) ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void eip197_write_firmware(struct safexcel_crypto_priv *priv,
				  const struct firmware *fw, int pe, u32 ctrl,
				  u32 prog_en)
{
	const u32 *data = (const u32 *)fw->data;
	u32 val;
	int i;

	/* Reset the engine to make its program memory accessible */
	writel(EIP197_PE_ICE_x_CTRL_SW_RESET |
	       EIP197_PE_ICE_x_CTRL_CLR_ECC_CORR |
	       EIP197_PE_ICE_x_CTRL_CLR_ECC_NON_CORR,
	       EIP197_PE(priv) + ctrl);

	/* Enable access to the program memory */
	writel(prog_en, EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));

	/* Write the firmware */
	for (i = 0; i < fw->size / sizeof(u32); i++)
		writel(be32_to_cpu(data[i]),
		       priv->base + EIP197_CLASSIFICATION_RAMS + i * sizeof(u32));

	/* Disable access to the program memory */
	writel(0, EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));

	/* Release engine from reset */
	val = readl(EIP197_PE(priv) + ctrl);
	val &= ~EIP197_PE_ICE_x_CTRL_SW_RESET;
	writel(val, EIP197_PE(priv) + ctrl);
}