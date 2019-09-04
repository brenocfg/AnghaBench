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
 int /*<<< orphan*/  CNIG_REG_NW_PORT_MODE_BB ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_hw_info_port_num_bb(struct qed_hwfn *p_hwfn,
				    struct qed_ptt *p_ptt)
{
	u32 port_mode;

	port_mode = qed_rd(p_hwfn, p_ptt, CNIG_REG_NW_PORT_MODE_BB);

	if (port_mode < 3) {
		p_hwfn->cdev->num_ports_in_engine = 1;
	} else if (port_mode <= 5) {
		p_hwfn->cdev->num_ports_in_engine = 2;
	} else {
		DP_NOTICE(p_hwfn, "PORT MODE: %d not supported\n",
			  p_hwfn->cdev->num_ports_in_engine);

		/* Default num_ports_in_engine to something */
		p_hwfn->cdev->num_ports_in_engine = 1;
	}
}