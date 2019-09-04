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
typedef  int u32 ;
struct TYPE_2__ {int pes; } ;
struct safexcel_crypto_priv {int version; TYPE_1__ config; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
#define  EIP197B 129 
#define  EIP197D 128 
 int EIP197_NUM_OF_SCRATCH_BLOCKS ; 
 scalar_t__ EIP197_PE (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  EIP197_PE_ICE_FPP_CTRL (int) ; 
 int /*<<< orphan*/  EIP197_PE_ICE_PUE_CTRL (int) ; 
 int /*<<< orphan*/  EIP197_PE_ICE_RAM_CTRL_FPP_PROG_EN ; 
 int /*<<< orphan*/  EIP197_PE_ICE_RAM_CTRL_PUE_PROG_EN ; 
 scalar_t__ EIP197_PE_ICE_SCRATCH_CTRL (int) ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_ACCESS ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_TIMER ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_SCRATCH_ACCESS ; 
 int EIP197_PE_ICE_SCRATCH_CTRL_TIMER_EN ; 
 scalar_t__ EIP197_PE_ICE_SCRATCH_RAM (int) ; 
 size_t FW_IFPP ; 
 size_t FW_IPUE ; 
 int FW_NB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  eip197_write_firmware (struct safexcel_crypto_priv*,struct firmware const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int eip197_load_firmwares(struct safexcel_crypto_priv *priv)
{
	const char *fw_name[] = {"ifpp.bin", "ipue.bin"};
	const struct firmware *fw[FW_NB];
	char fw_path[31], *dir = NULL;
	int i, j, ret = 0, pe;
	u32 val;

	switch (priv->version) {
	case EIP197B:
		dir = "eip197b";
		break;
	case EIP197D:
		dir = "eip197d";
		break;
	default:
		/* No firmware is required */
		return 0;
	}

	for (i = 0; i < FW_NB; i++) {
		snprintf(fw_path, 31, "inside-secure/%s/%s", dir, fw_name[i]);
		ret = request_firmware(&fw[i], fw_path, priv->dev);
		if (ret) {
			if (priv->version != EIP197B)
				goto release_fw;

			/* Fallback to the old firmware location for the
			 * EIP197b.
			 */
			ret = request_firmware(&fw[i], fw_name[i], priv->dev);
			if (ret) {
				dev_err(priv->dev,
					"Failed to request firmware %s (%d)\n",
					fw_name[i], ret);
				goto release_fw;
			}
		}
	}

	for (pe = 0; pe < priv->config.pes; pe++) {
		/* Clear the scratchpad memory */
		val = readl(EIP197_PE(priv) + EIP197_PE_ICE_SCRATCH_CTRL(pe));
		val |= EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_TIMER |
		       EIP197_PE_ICE_SCRATCH_CTRL_TIMER_EN |
		       EIP197_PE_ICE_SCRATCH_CTRL_SCRATCH_ACCESS |
		       EIP197_PE_ICE_SCRATCH_CTRL_CHANGE_ACCESS;
		writel(val, EIP197_PE(priv) + EIP197_PE_ICE_SCRATCH_CTRL(pe));

		memset_io(EIP197_PE(priv) + EIP197_PE_ICE_SCRATCH_RAM(pe), 0,
			  EIP197_NUM_OF_SCRATCH_BLOCKS * sizeof(u32));

		eip197_write_firmware(priv, fw[FW_IFPP], pe,
				      EIP197_PE_ICE_FPP_CTRL(pe),
				      EIP197_PE_ICE_RAM_CTRL_FPP_PROG_EN);

		eip197_write_firmware(priv, fw[FW_IPUE], pe,
				      EIP197_PE_ICE_PUE_CTRL(pe),
				      EIP197_PE_ICE_RAM_CTRL_PUE_PROG_EN);
	}

release_fw:
	for (j = 0; j < i; j++)
		release_firmware(fw[j]);

	return ret;
}