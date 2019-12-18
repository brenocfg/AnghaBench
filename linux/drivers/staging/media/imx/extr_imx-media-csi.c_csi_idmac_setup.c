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
struct csi_priv {int /*<<< orphan*/  idmac_ch; int /*<<< orphan*/  smfc; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int csi_idmac_setup_channel (struct csi_priv*) ; 
 int /*<<< orphan*/  ipu_cpmem_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_enable_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_select_buffer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_smfc_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int csi_idmac_setup(struct csi_priv *priv)
{
	int ret;

	ret = csi_idmac_setup_channel(priv);
	if (ret)
		return ret;

	ipu_cpmem_dump(priv->idmac_ch);
	ipu_dump(priv->ipu);

	ipu_smfc_enable(priv->smfc);

	/* set buffers ready */
	ipu_idmac_select_buffer(priv->idmac_ch, 0);
	ipu_idmac_select_buffer(priv->idmac_ch, 1);

	/* enable the channels */
	ipu_idmac_enable_channel(priv->idmac_ch);

	return 0;
}