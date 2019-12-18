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
struct meson_nfc {int /*<<< orphan*/  dev; scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_CMD_GET_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ NFC_REG_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int /*<<< orphan*/ ,int,int,unsigned int) ; 

__attribute__((used)) static int meson_nfc_wait_cmd_finish(struct meson_nfc *nfc,
				     unsigned int timeout_ms)
{
	u32 cmd_size = 0;
	int ret;

	/* wait cmd fifo is empty */
	ret = readl_relaxed_poll_timeout(nfc->reg_base + NFC_REG_CMD, cmd_size,
					 !NFC_CMD_GET_SIZE(cmd_size),
					 10, timeout_ms * 1000);
	if (ret)
		dev_err(nfc->dev, "wait for empty CMD FIFO time out\n");

	return ret;
}