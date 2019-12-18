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
struct s3c2410_nand_info {int cpu_type; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C2440_NFCONT ; 
 int /*<<< orphan*/  S3C2440_NFCONT_ENABLE ; 
#define  TYPE_S3C2410 130 
#define  TYPE_S3C2412 129 
#define  TYPE_S3C2440 128 
 int s3c2410_nand_setrate (struct s3c2410_nand_info*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c2410_nand_inithw(struct s3c2410_nand_info *info)
{
	int ret;

	ret = s3c2410_nand_setrate(info);
	if (ret < 0)
		return ret;

	switch (info->cpu_type) {
	case TYPE_S3C2410:
	default:
		break;

	case TYPE_S3C2440:
	case TYPE_S3C2412:
		/* enable the controller and de-assert nFCE */

		writel(S3C2440_NFCONT_ENABLE, info->regs + S3C2440_NFCONT);
	}

	return 0;
}