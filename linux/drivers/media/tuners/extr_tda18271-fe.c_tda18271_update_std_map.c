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
struct tda18271_std_map {int dummy; } ;
struct tda18271_priv {struct tda18271_std_map std; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atsc_6 ; 
 int /*<<< orphan*/  atv_b ; 
 int /*<<< orphan*/  atv_dk ; 
 int /*<<< orphan*/  atv_gh ; 
 int /*<<< orphan*/  atv_i ; 
 int /*<<< orphan*/  atv_l ; 
 int /*<<< orphan*/  atv_lc ; 
 int /*<<< orphan*/  atv_mn ; 
 int /*<<< orphan*/  dvbt_6 ; 
 int /*<<< orphan*/  dvbt_7 ; 
 int /*<<< orphan*/  dvbt_8 ; 
 int /*<<< orphan*/  fm_radio ; 
 int /*<<< orphan*/  qam_6 ; 
 int /*<<< orphan*/  qam_7 ; 
 int /*<<< orphan*/  qam_8 ; 
 int /*<<< orphan*/  tda18271_update_std (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tda18271_update_std_map(struct dvb_frontend *fe,
				   struct tda18271_std_map *map)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	struct tda18271_std_map *std = &priv->std;

	if (!map)
		return -EINVAL;

	tda18271_update_std(fm_radio, "fm");
	tda18271_update_std(atv_b,  "atv b");
	tda18271_update_std(atv_dk, "atv dk");
	tda18271_update_std(atv_gh, "atv gh");
	tda18271_update_std(atv_i,  "atv i");
	tda18271_update_std(atv_l,  "atv l");
	tda18271_update_std(atv_lc, "atv l'");
	tda18271_update_std(atv_mn, "atv mn");
	tda18271_update_std(atsc_6, "atsc 6");
	tda18271_update_std(dvbt_6, "dvbt 6");
	tda18271_update_std(dvbt_7, "dvbt 7");
	tda18271_update_std(dvbt_8, "dvbt 8");
	tda18271_update_std(qam_6,  "qam 6");
	tda18271_update_std(qam_7,  "qam 7");
	tda18271_update_std(qam_8,  "qam 8");

	return 0;
}