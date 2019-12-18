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
typedef  scalar_t__ u8 ;
struct dw_hdmi_cec {int addresses; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ CEC_LOG_ADDR_INVALID ; 
 int /*<<< orphan*/  HDMI_CEC_ADDR_H ; 
 int /*<<< orphan*/  HDMI_CEC_ADDR_L ; 
 struct dw_hdmi_cec* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  dw_hdmi_write (struct dw_hdmi_cec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_hdmi_cec_log_addr(struct cec_adapter *adap, u8 logical_addr)
{
	struct dw_hdmi_cec *cec = cec_get_drvdata(adap);

	if (logical_addr == CEC_LOG_ADDR_INVALID)
		cec->addresses = 0;
	else
		cec->addresses |= BIT(logical_addr) | BIT(15);

	dw_hdmi_write(cec, cec->addresses & 255, HDMI_CEC_ADDR_L);
	dw_hdmi_write(cec, cec->addresses >> 8, HDMI_CEC_ADDR_H);

	return 0;
}