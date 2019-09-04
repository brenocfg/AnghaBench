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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* cdev; } ;
struct TYPE_2__ {int num_ports_in_engine; } ;

/* Variables and functions */
 scalar_t__ CNIG_REG_NIG_PORT0_CONF_K2 ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int MAX_NUM_PORTS_K2 ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 

__attribute__((used)) static void qed_hw_info_port_num_ah(struct qed_hwfn *p_hwfn,
				    struct qed_ptt *p_ptt)
{
	u32 port;
	int i;

	p_hwfn->cdev->num_ports_in_engine = 0;

	for (i = 0; i < MAX_NUM_PORTS_K2; i++) {
		port = qed_rd(p_hwfn, p_ptt,
			      CNIG_REG_NIG_PORT0_CONF_K2 + (i * 4));
		if (port & 1)
			p_hwfn->cdev->num_ports_in_engine++;
	}

	if (!p_hwfn->cdev->num_ports_in_engine) {
		DP_NOTICE(p_hwfn, "All NIG ports are inactive\n");

		/* Default num_ports_in_engine to something */
		p_hwfn->cdev->num_ports_in_engine = 1;
	}
}