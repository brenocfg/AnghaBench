#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tp_params {int /*<<< orphan*/  use_5tuple_mode; int /*<<< orphan*/  pm_size; } ;
struct TYPE_6__ {int nports; } ;
struct TYPE_7__ {scalar_t__ regs; TYPE_1__ params; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_TP_GLOBAL_CONFIG ; 
 scalar_t__ A_TP_IN_CONFIG ; 
 scalar_t__ A_TP_OUT_CONFIG ; 
 scalar_t__ A_TP_TX_DROP_CONFIG ; 
 unsigned int DROP_MSEC ; 
 int /*<<< orphan*/  DROP_PKTS_CNT ; 
 int F_ENABLE_TX_DROP ; 
 int F_ENABLE_TX_ERROR ; 
 int F_OFFLOAD_DISABLE ; 
 int F_PATH_MTU ; 
 int F_TP_IN_CSPI_CHECK_IP_CSUM ; 
 int F_TP_IN_CSPI_CHECK_TCP_CSUM ; 
 int F_TP_IN_CSPI_CPL ; 
 int F_TP_IN_ESPI_CHECK_IP_CSUM ; 
 int F_TP_IN_ESPI_CHECK_TCP_CSUM ; 
 int F_TP_IN_ESPI_ETHERNET ; 
 int F_TP_OUT_CSPI_CPL ; 
 int F_TP_OUT_ESPI_ETHERNET ; 
 int F_TP_OUT_ESPI_GENERATE_IP_CSUM ; 
 int F_TP_OUT_ESPI_GENERATE_TCP_CSUM ; 
 int V_5TUPLE_LOOKUP (int /*<<< orphan*/ ) ; 
 int V_DROP_TICKS_CNT (int) ; 
 int V_IP_TTL (int) ; 
 int V_NUM_PKTS_DROPPED (int /*<<< orphan*/ ) ; 
 int V_SYN_COOKIE_PARAMETER (int) ; 
 scalar_t__ is_T2 (TYPE_2__*) ; 
 int /*<<< orphan*/  t1_is_asic (TYPE_2__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tp_init(adapter_t * ap, const struct tp_params *p,
		    unsigned int tp_clk)
{
	u32 val;

	if (!t1_is_asic(ap))
		return;

	val = F_TP_IN_CSPI_CPL | F_TP_IN_CSPI_CHECK_IP_CSUM |
		F_TP_IN_CSPI_CHECK_TCP_CSUM | F_TP_IN_ESPI_ETHERNET;
	if (!p->pm_size)
		val |= F_OFFLOAD_DISABLE;
	else
		val |= F_TP_IN_ESPI_CHECK_IP_CSUM | F_TP_IN_ESPI_CHECK_TCP_CSUM;
	writel(val, ap->regs + A_TP_IN_CONFIG);
	writel(F_TP_OUT_CSPI_CPL |
	       F_TP_OUT_ESPI_ETHERNET |
	       F_TP_OUT_ESPI_GENERATE_IP_CSUM |
	       F_TP_OUT_ESPI_GENERATE_TCP_CSUM, ap->regs + A_TP_OUT_CONFIG);
	writel(V_IP_TTL(64) |
	       F_PATH_MTU /* IP DF bit */  |
	       V_5TUPLE_LOOKUP(p->use_5tuple_mode) |
	       V_SYN_COOKIE_PARAMETER(29), ap->regs + A_TP_GLOBAL_CONFIG);
	/*
	 * Enable pause frame deadlock prevention.
	 */
	if (is_T2(ap) && ap->params.nports > 1) {
		u32 drop_ticks = DROP_MSEC * (tp_clk / 1000);

		writel(F_ENABLE_TX_DROP | F_ENABLE_TX_ERROR |
		       V_DROP_TICKS_CNT(drop_ticks) |
		       V_NUM_PKTS_DROPPED(DROP_PKTS_CNT),
		       ap->regs + A_TP_TX_DROP_CONFIG);
	}
}