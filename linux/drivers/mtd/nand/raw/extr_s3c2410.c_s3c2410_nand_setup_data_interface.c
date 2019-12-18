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
struct s3c2410_platform_nand {void* twrph1; void* twrph0; void* tacls; } ;
struct s3c2410_nand_info {struct s3c2410_platform_nand* platform; } ;
struct nand_sdr_timings {int tCLS_min; int tWP_min; int tCLH_min; } ;
struct nand_data_interface {int dummy; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (int,int) ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct nand_sdr_timings const*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (struct nand_data_interface const*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 struct s3c2410_nand_info* s3c2410_nand_mtd_toinfo (struct mtd_info*) ; 
 int s3c2410_nand_setrate (struct s3c2410_nand_info*) ; 

__attribute__((used)) static int s3c2410_nand_setup_data_interface(struct nand_chip *chip, int csline,
					const struct nand_data_interface *conf)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	struct s3c2410_platform_nand *pdata = info->platform;
	const struct nand_sdr_timings *timings;
	int tacls;

	timings = nand_get_sdr_timings(conf);
	if (IS_ERR(timings))
		return -ENOTSUPP;

	tacls = timings->tCLS_min - timings->tWP_min;
	if (tacls < 0)
		tacls = 0;

	pdata->tacls  = DIV_ROUND_UP(tacls, 1000);
	pdata->twrph0 = DIV_ROUND_UP(timings->tWP_min, 1000);
	pdata->twrph1 = DIV_ROUND_UP(timings->tCLH_min, 1000);

	return s3c2410_nand_setrate(info);
}