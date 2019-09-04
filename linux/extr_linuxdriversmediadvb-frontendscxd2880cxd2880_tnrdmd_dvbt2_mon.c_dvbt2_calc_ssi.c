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
typedef  enum cxd2880_dvbt2_plp_constell { ____Placeholder_cxd2880_dvbt2_plp_constell } cxd2880_dvbt2_plp_constell ;
typedef  enum cxd2880_dvbt2_plp_code_rate { ____Placeholder_cxd2880_dvbt2_plp_code_rate } cxd2880_dvbt2_plp_code_rate ;

/* Variables and functions */
 int /*<<< orphan*/  CXD2880_DVBT2_PLP_DATA ; 
 int CXD2880_DVBT2_QAM256 ; 
 int CXD2880_DVBT2_R2_5 ; 
 int EINVAL ; 
 int cxd2880_tnrdmd_dvbt2_mon_code_rate (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int*) ; 
 int cxd2880_tnrdmd_dvbt2_mon_qam (struct cxd2880_tnrdmd*,int /*<<< orphan*/ ,int*) ; 
 int** ref_dbm_1000 ; 

__attribute__((used)) static int dvbt2_calc_ssi(struct cxd2880_tnrdmd *tnr_dmd,
			  int rf_lvl, u8 *ssi)
{
	enum cxd2880_dvbt2_plp_constell qam;
	enum cxd2880_dvbt2_plp_code_rate code_rate;
	int prel;
	int temp_ssi = 0;
	int ret;

	if (!tnr_dmd || !ssi)
		return -EINVAL;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_qam(tnr_dmd, CXD2880_DVBT2_PLP_DATA, &qam);
	if (ret)
		return ret;

	ret =
	    cxd2880_tnrdmd_dvbt2_mon_code_rate(tnr_dmd, CXD2880_DVBT2_PLP_DATA,
					       &code_rate);
	if (ret)
		return ret;

	if (code_rate > CXD2880_DVBT2_R2_5 || qam > CXD2880_DVBT2_QAM256)
		return -EINVAL;

	prel = rf_lvl - ref_dbm_1000[qam][code_rate];

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