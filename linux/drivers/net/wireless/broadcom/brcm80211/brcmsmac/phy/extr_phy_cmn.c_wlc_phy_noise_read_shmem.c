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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_4__ {size_t phy_corenum; } ;
struct brcms_phy {size_t nphy_noise_index; scalar_t__** nphy_noise_win; TYPE_2__ pubpi; TYPE_1__* sh; } ;
typedef  scalar_t__ s8 ;
typedef  int /*<<< orphan*/  noise_dbm_ant ;
typedef  int /*<<< orphan*/  cmplx_pwr ;
struct TYPE_3__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 size_t MODINC_POW2 (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PWRIND_MAP (size_t) ; 
 int PHY_CORE_MAX ; 
 scalar_t__ PHY_NOISE_FIXED_VAL_NPHY ; 
 scalar_t__ PHY_NOISE_SAMPLE_LOG_NUM_UCODE ; 
 int /*<<< orphan*/  PHY_NOISE_WINDOW_SZ ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int wlapi_bmac_read_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_noise_calc_phy (struct brcms_phy*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static s8 wlc_phy_noise_read_shmem(struct brcms_phy *pi)
{
	u32 cmplx_pwr[PHY_CORE_MAX];
	s8 noise_dbm_ant[PHY_CORE_MAX];
	u16 lo, hi;
	u32 cmplx_pwr_tot = 0;
	s8 noise_dbm = PHY_NOISE_FIXED_VAL_NPHY;
	u8 idx, core;

	memset((u8 *) cmplx_pwr, 0, sizeof(cmplx_pwr));
	memset((u8 *) noise_dbm_ant, 0, sizeof(noise_dbm_ant));

	for (idx = 0, core = 0; core < pi->pubpi.phy_corenum; idx += 2,
	     core++) {
		lo = wlapi_bmac_read_shm(pi->sh->physhim, M_PWRIND_MAP(idx));
		hi = wlapi_bmac_read_shm(pi->sh->physhim,
					 M_PWRIND_MAP(idx + 1));
		cmplx_pwr[core] = (hi << 16) + lo;
		cmplx_pwr_tot += cmplx_pwr[core];
		if (cmplx_pwr[core] == 0)
			noise_dbm_ant[core] = PHY_NOISE_FIXED_VAL_NPHY;
		else
			cmplx_pwr[core] >>= PHY_NOISE_SAMPLE_LOG_NUM_UCODE;
	}

	if (cmplx_pwr_tot != 0)
		wlc_phy_noise_calc_phy(pi, cmplx_pwr, noise_dbm_ant);

	for (core = 0; core < pi->pubpi.phy_corenum; core++) {
		pi->nphy_noise_win[core][pi->nphy_noise_index] =
			noise_dbm_ant[core];

		if (noise_dbm_ant[core] > noise_dbm)
			noise_dbm = noise_dbm_ant[core];
	}
	pi->nphy_noise_index =
		MODINC_POW2(pi->nphy_noise_index, PHY_NOISE_WINDOW_SZ);

	return noise_dbm;

}