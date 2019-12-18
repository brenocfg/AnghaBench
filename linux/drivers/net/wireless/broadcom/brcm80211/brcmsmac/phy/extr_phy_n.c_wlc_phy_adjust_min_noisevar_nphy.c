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
struct TYPE_2__ {int bufcount; int* tone_id; int* min_noise_vars; } ;
struct brcms_phy {int nphy_noisevars_adjusted; TYPE_1__ nphy_saved_noisevars; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int NPHY_NOISEVAR_TBLLEN20 ; 
 int NPHY_NOISEVAR_TBLLEN40 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_NOISEVAR ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 

__attribute__((used)) static void
wlc_phy_adjust_min_noisevar_nphy(struct brcms_phy *pi, int ntones,
				 int *tone_id_buf, u32 *noise_var_buf)
{
	int i;
	u32 offset;
	int tone_id;
	int tbllen =
		CHSPEC_IS40(pi->radio_chanspec) ?
		NPHY_NOISEVAR_TBLLEN40 : NPHY_NOISEVAR_TBLLEN20;

	if (pi->nphy_noisevars_adjusted) {
		for (i = 0; i < pi->nphy_saved_noisevars.bufcount; i++) {
			tone_id = pi->nphy_saved_noisevars.tone_id[i];
			offset = (tone_id >= 0) ?
				 ((tone_id *
				   2) + 1) : (tbllen + (tone_id * 2) + 1);
			wlc_phy_table_write_nphy(
				pi, NPHY_TBL_ID_NOISEVAR, 1,
				offset, 32,
				&pi->nphy_saved_noisevars.min_noise_vars[i]);
		}

		pi->nphy_saved_noisevars.bufcount = 0;
		pi->nphy_noisevars_adjusted = false;
	}

	if ((noise_var_buf != NULL) && (tone_id_buf != NULL)) {
		pi->nphy_saved_noisevars.bufcount = 0;

		for (i = 0; i < ntones; i++) {
			tone_id = tone_id_buf[i];
			offset = (tone_id >= 0) ?
				 ((tone_id * 2) + 1) :
				 (tbllen + (tone_id * 2) + 1);
			pi->nphy_saved_noisevars.tone_id[i] = tone_id;
			wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_NOISEVAR, 1,
						offset, 32,
						&pi->nphy_saved_noisevars.
						min_noise_vars[i]);
			wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_NOISEVAR, 1,
						 offset, 32, &noise_var_buf[i]);
			pi->nphy_saved_noisevars.bufcount++;
		}

		pi->nphy_noisevars_adjusted = true;
	}
}