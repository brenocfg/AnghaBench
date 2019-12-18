#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mt7601u_tssi_params {int tssi0; int trgt_power; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct mt7601u_dev {int tssi_init_hvga; int tssi_init; int prev_pwr_diff; int /*<<< orphan*/  dev; TYPE_4__* ee; scalar_t__ tssi_init_hvga_offset_db; TYPE_2__ chandef; int /*<<< orphan*/  tssi_read_trig; } ;
typedef  int s8 ;
typedef  char s16 ;
struct TYPE_7__ {char* offset; char slope; } ;
struct TYPE_8__ {TYPE_3__ tssi_data; int /*<<< orphan*/  tssi_enabled; } ;
struct TYPE_5__ {int hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int,int) ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_1 ; 
 int MT_TX_ALC_CFG_1_TEMP_COMP ; 
 int abs (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int int_to_s6 (int) ; 
 char lin2dBd (char) ; 
 int mt7601u_mcu_tssi_read_kick (struct mt7601u_dev*,int) ; 
 int mt7601u_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 struct mt7601u_tssi_params mt7601u_tssi_params_get (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_tssi_read_ready (struct mt7601u_dev*) ; 
 int mt7601u_use_hvga (struct mt7601u_dev*) ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int s6_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_tssi_cal(struct mt7601u_dev *dev)
{
	struct mt7601u_tssi_params params;
	int curr_pwr, diff_pwr;
	char tssi_offset;
	s8 tssi_init;
	s16 tssi_m_dc, tssi_db;
	bool hvga;
	u32 val;

	if (!dev->ee->tssi_enabled)
		return 0;

	hvga = mt7601u_use_hvga(dev);
	if (!dev->tssi_read_trig)
		return mt7601u_mcu_tssi_read_kick(dev, hvga);

	if (!mt7601u_tssi_read_ready(dev))
		return 0;

	params = mt7601u_tssi_params_get(dev);

	tssi_init = (hvga ? dev->tssi_init_hvga : dev->tssi_init);
	tssi_m_dc = params.tssi0 - tssi_init;
	tssi_db = lin2dBd(tssi_m_dc);
	dev_dbg(dev->dev, "tssi dc:%04hx db:%04hx hvga:%d\n",
		tssi_m_dc, tssi_db, hvga);

	if (dev->chandef.chan->hw_value < 5)
		tssi_offset = dev->ee->tssi_data.offset[0];
	else if (dev->chandef.chan->hw_value < 9)
		tssi_offset = dev->ee->tssi_data.offset[1];
	else
		tssi_offset = dev->ee->tssi_data.offset[2];

	if (hvga)
		tssi_db -= dev->tssi_init_hvga_offset_db;

	curr_pwr = tssi_db * dev->ee->tssi_data.slope + (tssi_offset << 9);
	diff_pwr = params.trgt_power - curr_pwr;
	dev_dbg(dev->dev, "Power curr:%08x diff:%08x\n", curr_pwr, diff_pwr);

	if (params.tssi0 > 126 && diff_pwr > 0) {
		dev_err(dev->dev, "Error: TSSI upper saturation\n");
		diff_pwr = 0;
	}
	if (params.tssi0 - tssi_init < 1 && diff_pwr < 0) {
		dev_err(dev->dev, "Error: TSSI lower saturation\n");
		diff_pwr = 0;
	}

	if ((dev->prev_pwr_diff ^ diff_pwr) < 0 && abs(diff_pwr) < 4096 &&
	    (abs(diff_pwr) > abs(dev->prev_pwr_diff) ||
	     (diff_pwr > 0 && diff_pwr == -dev->prev_pwr_diff)))
		diff_pwr = 0;
	else
		dev->prev_pwr_diff = diff_pwr;

	diff_pwr += (diff_pwr > 0) ? 2048 : -2048;
	diff_pwr /= 4096;

	dev_dbg(dev->dev, "final diff: %08x\n", diff_pwr);

	val = mt7601u_rr(dev, MT_TX_ALC_CFG_1);
	curr_pwr = s6_to_int(FIELD_GET(MT_TX_ALC_CFG_1_TEMP_COMP, val));
	diff_pwr += curr_pwr;
	val = (val & ~MT_TX_ALC_CFG_1_TEMP_COMP) | int_to_s6(diff_pwr);
	mt7601u_wr(dev, MT_TX_ALC_CFG_1, val);

	return mt7601u_mcu_tssi_read_kick(dev, hvga);
}