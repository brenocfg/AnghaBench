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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ v4l2_dev; } ;
struct sh_mobile_ceu_dev {TYPE_2__ ici; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPSR ; 
 int /*<<< orphan*/  CSTSR ; 
 int EIO ; 
 int ceu_read (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sh_mobile_ceu_soft_reset(struct sh_mobile_ceu_dev *pcdev)
{
	int i, success = 0;

	ceu_write(pcdev, CAPSR, 1 << 16); /* reset */

	/* wait CSTSR.CPTON bit */
	for (i = 0; i < 1000; i++) {
		if (!(ceu_read(pcdev, CSTSR) & 1)) {
			success++;
			break;
		}
		udelay(1);
	}

	/* wait CAPSR.CPKIL bit */
	for (i = 0; i < 1000; i++) {
		if (!(ceu_read(pcdev, CAPSR) & (1 << 16))) {
			success++;
			break;
		}
		udelay(1);
	}

	if (2 != success) {
		dev_warn(pcdev->ici.v4l2_dev.dev, "soft reset time out\n");
		return -EIO;
	}

	return 0;
}