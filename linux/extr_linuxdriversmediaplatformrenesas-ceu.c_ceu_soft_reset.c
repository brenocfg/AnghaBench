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
struct ceu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEU_CAPSR ; 
 int CEU_CAPSR_CPKIL ; 
 int CEU_CSTRST_CPTON ; 
 int /*<<< orphan*/  CEU_CSTSR ; 
 int EIO ; 
 int ceu_read (struct ceu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceu_write (struct ceu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ceu_soft_reset(struct ceu_device *ceudev)
{
	unsigned int i;

	ceu_write(ceudev, CEU_CAPSR, CEU_CAPSR_CPKIL);

	for (i = 0; i < 100; i++) {
		if (!(ceu_read(ceudev, CEU_CSTSR) & CEU_CSTRST_CPTON))
			break;
		udelay(1);
	}

	if (i == 100) {
		dev_err(ceudev->dev, "soft reset time out\n");
		return -EIO;
	}

	for (i = 0; i < 100; i++) {
		if (!(ceu_read(ceudev, CEU_CAPSR) & CEU_CAPSR_CPKIL))
			return 0;
		udelay(1);
	}

	/* If we get here, CEU has not reset properly. */
	return -EIO;
}