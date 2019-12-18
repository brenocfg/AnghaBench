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
struct i2400m_tlv_rf_switches_status {int /*<<< orphan*/  hw_rf_switch; int /*<<< orphan*/  sw_rf_switch; } ;
struct i2400m {int /*<<< orphan*/  wimax_dev; } ;
struct device {int dummy; } ;
typedef  enum wimax_st { ____Placeholder_wimax_st } wimax_st ;
typedef  enum i2400m_rf_switch_status { ____Placeholder_i2400m_rf_switch_status } i2400m_rf_switch_status ;

/* Variables and functions */
#define  I2400M_RF_SWITCH_OFF 129 
#define  I2400M_RF_SWITCH_ON 128 
 int /*<<< orphan*/  WIMAX_RF_OFF ; 
 int /*<<< orphan*/  WIMAX_RF_ON ; 
 int WIMAX_ST_RADIO_OFF ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*,struct i2400m_tlv_rf_switches_status const*,int,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*,struct i2400m_tlv_rf_switches_status const*,int,int) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wimax_report_rfkill_hw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wimax_report_rfkill_sw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wimax_state_get (int /*<<< orphan*/ *) ; 

void i2400m_report_tlv_rf_switches_status(
	struct i2400m *i2400m,
	const struct i2400m_tlv_rf_switches_status *rfss)
{
	struct device *dev = i2400m_dev(i2400m);
	enum i2400m_rf_switch_status hw, sw;
	enum wimax_st wimax_state;

	sw = le32_to_cpu(rfss->sw_rf_switch);
	hw = le32_to_cpu(rfss->hw_rf_switch);

	d_fnstart(3, dev, "(i2400m %p rfss %p [hw %u sw %u])\n",
		  i2400m, rfss, hw, sw);
	/* We only process rw switch evens when the device has been
	 * fully initialized */
	wimax_state = wimax_state_get(&i2400m->wimax_dev);
	if (wimax_state < WIMAX_ST_RADIO_OFF) {
		d_printf(3, dev, "ignoring RF switches report, state %u\n",
			 wimax_state);
		goto out;
	}
	switch (sw) {
	case I2400M_RF_SWITCH_ON:	/* RF Kill disabled (radio on) */
		wimax_report_rfkill_sw(&i2400m->wimax_dev, WIMAX_RF_ON);
		break;
	case I2400M_RF_SWITCH_OFF:	/* RF Kill enabled (radio off) */
		wimax_report_rfkill_sw(&i2400m->wimax_dev, WIMAX_RF_OFF);
		break;
	default:
		dev_err(dev, "HW BUG? Unknown RF SW state 0x%x\n", sw);
	}

	switch (hw) {
	case I2400M_RF_SWITCH_ON:	/* RF Kill disabled (radio on) */
		wimax_report_rfkill_hw(&i2400m->wimax_dev, WIMAX_RF_ON);
		break;
	case I2400M_RF_SWITCH_OFF:	/* RF Kill enabled (radio off) */
		wimax_report_rfkill_hw(&i2400m->wimax_dev, WIMAX_RF_OFF);
		break;
	default:
		dev_err(dev, "HW BUG? Unknown RF HW state 0x%x\n", hw);
	}
out:
	d_fnend(3, dev, "(i2400m %p rfss %p [hw %u sw %u]) = void\n",
		i2400m, rfss, hw, sw);
}