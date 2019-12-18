#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct firmware {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct bdx_priv {TYPE_2__* ndev; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int EIO ; 
 int /*<<< orphan*/  ENTER ; 
 int READ_REG (struct bdx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RET (int) ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bdx_tx_push_desc_safe (struct bdx_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  regINIT_SEMAPHORE ; 
 int /*<<< orphan*/  regINIT_STATUS ; 
 int /*<<< orphan*/  regVIC ; 
 int /*<<< orphan*/  regVPC ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bdx_fw_load(struct bdx_priv *priv)
{
	const struct firmware *fw = NULL;
	int master, i;
	int rc;

	ENTER;
	master = READ_REG(priv, regINIT_SEMAPHORE);
	if (!READ_REG(priv, regINIT_STATUS) && master) {
		rc = request_firmware(&fw, "tehuti/bdx.bin", &priv->pdev->dev);
		if (rc)
			goto out;
		bdx_tx_push_desc_safe(priv, (char *)fw->data, fw->size);
		mdelay(100);
	}
	for (i = 0; i < 200; i++) {
		if (READ_REG(priv, regINIT_STATUS)) {
			rc = 0;
			goto out;
		}
		mdelay(2);
	}
	rc = -EIO;
out:
	if (master)
		WRITE_REG(priv, regINIT_SEMAPHORE, 1);

	release_firmware(fw);

	if (rc) {
		netdev_err(priv->ndev, "firmware loading failed\n");
		if (rc == -EIO)
			DBG("VPC = 0x%x VIC = 0x%x INIT_STATUS = 0x%x i=%d\n",
			    READ_REG(priv, regVPC),
			    READ_REG(priv, regVIC),
			    READ_REG(priv, regINIT_STATUS), i);
		RET(rc);
	} else {
		DBG("%s: firmware loading success\n", priv->ndev->name);
		RET(0);
	}
}