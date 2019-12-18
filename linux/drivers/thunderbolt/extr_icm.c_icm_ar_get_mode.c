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
struct tb_nhi {TYPE_1__* pdev; scalar_t__ iobase; } ;
struct tb {struct tb_nhi* nhi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ REG_FW_STS ; 
 int REG_FW_STS_NVM_AUTH_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int nhi_mailbox_mode (struct tb_nhi*) ; 

__attribute__((used)) static int icm_ar_get_mode(struct tb *tb)
{
	struct tb_nhi *nhi = tb->nhi;
	int retries = 60;
	u32 val;

	do {
		val = ioread32(nhi->iobase + REG_FW_STS);
		if (val & REG_FW_STS_NVM_AUTH_DONE)
			break;
		msleep(50);
	} while (--retries);

	if (!retries) {
		dev_err(&nhi->pdev->dev, "ICM firmware not authenticated\n");
		return -ENODEV;
	}

	return nhi_mailbox_mode(nhi);
}