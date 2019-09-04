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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct stih_cec {scalar_t__ regs; } ;
struct cec_msg {int len; int /*<<< orphan*/ * msg; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ CEC_TX_ARRAY_CTRL ; 
 int CEC_TX_AUTO_EOM_EN ; 
 int CEC_TX_AUTO_SOM_EN ; 
 scalar_t__ CEC_TX_DATA_BASE ; 
 int CEC_TX_START ; 
 struct stih_cec* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stih_cec_adap_transmit(struct cec_adapter *adap, u8 attempts,
				  u32 signal_free_time, struct cec_msg *msg)
{
	struct stih_cec *cec = cec_get_drvdata(adap);
	int i;

	/* Copy message into registers */
	for (i = 0; i < msg->len; i++)
		writeb(msg->msg[i], cec->regs + CEC_TX_DATA_BASE + i);

	/*
	 * Start transmission, configure hardware to add start and stop bits
	 * Signal free time is handled by the hardware
	 */
	writel(CEC_TX_AUTO_SOM_EN | CEC_TX_AUTO_EOM_EN | CEC_TX_START |
	       msg->len, cec->regs + CEC_TX_ARRAY_CTRL);

	return 0;
}