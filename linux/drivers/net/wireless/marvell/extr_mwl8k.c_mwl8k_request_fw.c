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
struct mwl8k_priv {TYPE_1__* pdev; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  mwl8k_fw_state_machine ; 
 int /*<<< orphan*/  mwl8k_release_fw (struct firmware const**) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mwl8k_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwl8k_request_fw(struct mwl8k_priv *priv,
			    const char *fname, const struct firmware **fw,
			    bool nowait)
{
	/* release current image */
	if (*fw != NULL)
		mwl8k_release_fw(fw);

	if (nowait)
		return request_firmware_nowait(THIS_MODULE, 1, fname,
					       &priv->pdev->dev, GFP_KERNEL,
					       priv, mwl8k_fw_state_machine);
	else
		return request_firmware(fw, fname, &priv->pdev->dev);
}