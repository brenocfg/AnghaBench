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
struct hdmi_core_data {int /*<<< orphan*/  base; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ FLD_GET (int,int,int) ; 
 int /*<<< orphan*/  HDMI_CEC_DBG_3 ; 
 int HDMI_CORE_CEC_RETRY ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct hdmi_core_data* cec_get_drvdata (struct cec_adapter*) ; 
 int hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hdmi_cec_clear_tx_fifo(struct cec_adapter *adap)
{
	struct hdmi_core_data *core = cec_get_drvdata(adap);
	int retry = HDMI_CORE_CEC_RETRY;
	int temp;

	REG_FLD_MOD(core->base, HDMI_CEC_DBG_3, 0x1, 7, 7);
	while (retry) {
		temp = hdmi_read_reg(core->base, HDMI_CEC_DBG_3);
		if (FLD_GET(temp, 7, 7) == 0)
			break;
		retry--;
	}
	return retry != 0;
}