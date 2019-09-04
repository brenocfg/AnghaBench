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
struct stih_cec {scalar_t__ regs; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ CEC_ADDR_TABLE ; 
 int CEC_LOG_ADDR_INVALID ; 
 struct stih_cec* cec_get_drvdata (struct cec_adapter*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stih_cec_adap_log_addr(struct cec_adapter *adap, u8 logical_addr)
{
	struct stih_cec *cec = cec_get_drvdata(adap);
	u32 reg = readl(cec->regs + CEC_ADDR_TABLE);

	reg |= 1 << logical_addr;

	if (logical_addr == CEC_LOG_ADDR_INVALID)
		reg = 0;

	writel(reg, cec->regs + CEC_ADDR_TABLE);

	return 0;
}