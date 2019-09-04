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
typedef  int u8 ;
struct cxd2880_tnrdmd {int dummy; } ;
struct cxd2880_dvbt_tpsinfo {size_t constellation; size_t rate_hp; } ;

/* Variables and functions */
 size_t CXD2880_DVBT_CODERATE_RESERVED_5 ; 
 size_t CXD2880_DVBT_CONSTELLATION_RESERVED_3 ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt_mon_tps_info (struct cxd2880_tnrdmd*,struct cxd2880_dvbt_tpsinfo*) ; 
 int** ref_dbm_1000 ; 

__attribute__((used)) static int dvbt_calc_ssi(struct cxd2880_tnrdmd *tnr_dmd,
			 int rf_lvl, u8 *ssi)
{
	struct cxd2880_dvbt_tpsinfo tps;
	int prel;
	int temp_ssi = 0;
	int ret;

	if (!tnr_dmd || !ssi)
		return -EINVAL;

	ret = cxd2880_tnrdmd_dvbt_mon_tps_info(tnr_dmd, &tps);
	if (ret)
		return ret;

	if (tps.constellation >= CXD2880_DVBT_CONSTELLATION_RESERVED_3 ||
	    tps.rate_hp >= CXD2880_DVBT_CODERATE_RESERVED_5)
		return -EINVAL;

	prel = rf_lvl - ref_dbm_1000[tps.constellation][tps.rate_hp];

	if (prel < -15000)
		temp_ssi = 0;
	else if (prel < 0)
		temp_ssi = ((2 * (prel + 15000)) + 1500) / 3000;
	else if (prel < 20000)
		temp_ssi = (((4 * prel) + 500) / 1000) + 10;
	else if (prel < 35000)
		temp_ssi = (((2 * (prel - 20000)) + 1500) / 3000) + 90;
	else
		temp_ssi = 100;

	*ssi = (temp_ssi > 100) ? 100 : (u8)temp_ssi;

	return ret;
}