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
typedef  int u32 ;
struct hdmi_core_data {int /*<<< orphan*/  base; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int CEC_LOG_ADDR_INVALID ; 
 int /*<<< orphan*/  HDMI_CEC_CA_15_8 ; 
 int /*<<< orphan*/  HDMI_CEC_CA_7_0 ; 
 struct hdmi_core_data* cec_get_drvdata (struct cec_adapter*) ; 
 int hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdmi_cec_adap_log_addr(struct cec_adapter *adap, u8 log_addr)
{
	struct hdmi_core_data *core = cec_get_drvdata(adap);
	u32 v;

	if (log_addr == CEC_LOG_ADDR_INVALID) {
		hdmi_write_reg(core->base, HDMI_CEC_CA_7_0, 0);
		hdmi_write_reg(core->base, HDMI_CEC_CA_15_8, 0);
		return 0;
	}
	if (log_addr <= 7) {
		v = hdmi_read_reg(core->base, HDMI_CEC_CA_7_0);
		v |= 1 << log_addr;
		hdmi_write_reg(core->base, HDMI_CEC_CA_7_0, v);
	} else {
		v = hdmi_read_reg(core->base, HDMI_CEC_CA_15_8);
		v |= 1 << (log_addr - 8);
		hdmi_write_reg(core->base, HDMI_CEC_CA_15_8, v);
	}
	return 0;
}