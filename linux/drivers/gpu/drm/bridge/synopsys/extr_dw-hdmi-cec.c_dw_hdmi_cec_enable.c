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
struct dw_hdmi_cec {int /*<<< orphan*/  hdmi; TYPE_1__* ops; int /*<<< orphan*/  adap; } ;
struct cec_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_LOG_ADDR_INVALID ; 
 unsigned int CEC_STAT_DONE ; 
 unsigned int CEC_STAT_EOM ; 
 unsigned int CEC_STAT_ERROR_INIT ; 
 unsigned int CEC_STAT_NACK ; 
 int /*<<< orphan*/  HDMI_CEC_CTRL ; 
 int /*<<< orphan*/  HDMI_CEC_LOCK ; 
 int /*<<< orphan*/  HDMI_CEC_MASK ; 
 int /*<<< orphan*/  HDMI_CEC_POLARITY ; 
 int /*<<< orphan*/  HDMI_IH_CEC_STAT0 ; 
 int /*<<< orphan*/  HDMI_IH_MUTE_CEC_STAT0 ; 
 struct dw_hdmi_cec* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  dw_hdmi_cec_log_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_hdmi_write (struct dw_hdmi_cec*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_hdmi_cec_enable(struct cec_adapter *adap, bool enable)
{
	struct dw_hdmi_cec *cec = cec_get_drvdata(adap);

	if (!enable) {
		dw_hdmi_write(cec, ~0, HDMI_CEC_MASK);
		dw_hdmi_write(cec, ~0, HDMI_IH_MUTE_CEC_STAT0);
		dw_hdmi_write(cec, 0, HDMI_CEC_POLARITY);

		cec->ops->disable(cec->hdmi);
	} else {
		unsigned int irqs;

		dw_hdmi_write(cec, 0, HDMI_CEC_CTRL);
		dw_hdmi_write(cec, ~0, HDMI_IH_CEC_STAT0);
		dw_hdmi_write(cec, 0, HDMI_CEC_LOCK);

		dw_hdmi_cec_log_addr(cec->adap, CEC_LOG_ADDR_INVALID);

		cec->ops->enable(cec->hdmi);

		irqs = CEC_STAT_ERROR_INIT | CEC_STAT_NACK | CEC_STAT_EOM |
		       CEC_STAT_DONE;
		dw_hdmi_write(cec, irqs, HDMI_CEC_POLARITY);
		dw_hdmi_write(cec, ~irqs, HDMI_CEC_MASK);
		dw_hdmi_write(cec, ~irqs, HDMI_IH_MUTE_CEC_STAT0);
	}
	return 0;
}