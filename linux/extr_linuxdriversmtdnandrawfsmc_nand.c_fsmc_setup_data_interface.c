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
struct nand_sdr_timings {int dummy; } ;
struct nand_data_interface {int dummy; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct fsmc_nand_timings {int dummy; } ;
struct fsmc_nand_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nand_sdr_timings const*) ; 
 int NAND_DATA_IFACE_CHECK_ONLY ; 
 int PTR_ERR (struct nand_sdr_timings const*) ; 
 int fsmc_calc_timings (struct fsmc_nand_data*,struct nand_sdr_timings const*,struct fsmc_nand_timings*) ; 
 int /*<<< orphan*/  fsmc_nand_setup (struct fsmc_nand_data*,struct fsmc_nand_timings*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct fsmc_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (struct nand_data_interface const*) ; 

__attribute__((used)) static int fsmc_setup_data_interface(struct mtd_info *mtd, int csline,
				     const struct nand_data_interface *conf)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct fsmc_nand_data *host = nand_get_controller_data(nand);
	struct fsmc_nand_timings tims;
	const struct nand_sdr_timings *sdrt;
	int ret;

	sdrt = nand_get_sdr_timings(conf);
	if (IS_ERR(sdrt))
		return PTR_ERR(sdrt);

	ret = fsmc_calc_timings(host, sdrt, &tims);
	if (ret)
		return ret;

	if (csline == NAND_DATA_IFACE_CHECK_ONLY)
		return 0;

	fsmc_nand_setup(host, &tims);

	return 0;
}