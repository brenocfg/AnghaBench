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
typedef  int u16 ;
struct m88rs6000t_dev {TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct dvb_frontend {struct m88rs6000t_dev* tuner_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int clamp_val (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int m88rs6000t_get_rf_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct m88rs6000t_dev *dev = fe->tuner_priv;
	unsigned int val, i;
	int ret;
	u16 gain;
	u32 PGA2_cri_GS = 46, PGA2_crf_GS = 290, TIA_GS = 290;
	u32 RF_GC = 1200, IF_GC = 1100, BB_GC = 300;
	u32 PGA2_GC = 300, TIA_GC = 300, PGA2_cri = 0, PGA2_crf = 0;
	u32 RFG = 0, IFG = 0, BBG = 0, PGA2G = 0, TIAG = 0;
	u32 RFGS[13] = {0, 245, 266, 268, 270, 285,
			298, 295, 283, 285, 285, 300, 300};
	u32 IFGS[12] = {0, 300, 230, 270, 270, 285,
			295, 285, 290, 295, 295, 310};
	u32 BBGS[14] = {0, 286, 275, 290, 294, 300, 290,
			290, 285, 283, 260, 295, 290, 260};

	ret = regmap_read(dev->regmap, 0x5A, &val);
	if (ret)
		goto err;
	RF_GC = val & 0x0f;

	ret = regmap_read(dev->regmap, 0x5F, &val);
	if (ret)
		goto err;
	IF_GC = val & 0x0f;

	ret = regmap_read(dev->regmap, 0x3F, &val);
	if (ret)
		goto err;
	TIA_GC = (val >> 4) & 0x07;

	ret = regmap_read(dev->regmap, 0x77, &val);
	if (ret)
		goto err;
	BB_GC = (val >> 4) & 0x0f;

	ret = regmap_read(dev->regmap, 0x76, &val);
	if (ret)
		goto err;
	PGA2_GC = val & 0x3f;
	PGA2_cri = PGA2_GC >> 2;
	PGA2_crf = PGA2_GC & 0x03;

	for (i = 0; i <= RF_GC; i++)
		RFG += RFGS[i];

	if (RF_GC == 0)
		RFG += 400;
	if (RF_GC == 1)
		RFG += 300;
	if (RF_GC == 2)
		RFG += 200;
	if (RF_GC == 3)
		RFG += 100;

	for (i = 0; i <= IF_GC; i++)
		IFG += IFGS[i];

	TIAG = TIA_GC * TIA_GS;

	for (i = 0; i <= BB_GC; i++)
		BBG += BBGS[i];

	PGA2G = PGA2_cri * PGA2_cri_GS + PGA2_crf * PGA2_crf_GS;

	gain = RFG + IFG - TIAG + BBG + PGA2G;

	/* scale value to 0x0000-0xffff */
	gain = clamp_val(gain, 1000U, 10500U);
	*strength = (10500 - gain) * 0xffff / (10500 - 1000);
err:
	if (ret)
		dev_dbg(&dev->client->dev, "failed=%d\n", ret);
	return ret;
}