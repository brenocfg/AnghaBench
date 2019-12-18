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
struct sh_mmcif_host {int dummy; } ;
struct mmc_request {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MMC_READ_MULTIPLE_BLOCK 132 
#define  MMC_READ_SINGLE_BLOCK 131 
#define  MMC_SEND_EXT_CSD 130 
#define  MMC_WRITE_BLOCK 129 
#define  MMC_WRITE_MULTIPLE_BLOCK 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* sh_mmcif_host_to_dev (struct sh_mmcif_host*) ; 
 int /*<<< orphan*/  sh_mmcif_multi_read (struct sh_mmcif_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sh_mmcif_multi_write (struct sh_mmcif_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sh_mmcif_single_read (struct sh_mmcif_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sh_mmcif_single_write (struct sh_mmcif_host*,struct mmc_request*) ; 

__attribute__((used)) static int sh_mmcif_data_trans(struct sh_mmcif_host *host,
			       struct mmc_request *mrq, u32 opc)
{
	struct device *dev = sh_mmcif_host_to_dev(host);

	switch (opc) {
	case MMC_READ_MULTIPLE_BLOCK:
		sh_mmcif_multi_read(host, mrq);
		return 0;
	case MMC_WRITE_MULTIPLE_BLOCK:
		sh_mmcif_multi_write(host, mrq);
		return 0;
	case MMC_WRITE_BLOCK:
		sh_mmcif_single_write(host, mrq);
		return 0;
	case MMC_READ_SINGLE_BLOCK:
	case MMC_SEND_EXT_CSD:
		sh_mmcif_single_read(host, mrq);
		return 0;
	default:
		dev_err(dev, "Unsupported CMD%d\n", opc);
		return -EINVAL;
	}
}