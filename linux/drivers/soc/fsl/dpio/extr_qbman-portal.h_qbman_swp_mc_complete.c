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
struct qbman_swp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* qbman_swp_mc_result (struct qbman_swp*) ; 
 int /*<<< orphan*/  qbman_swp_mc_submit (struct qbman_swp*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *qbman_swp_mc_complete(struct qbman_swp *swp, void *cmd,
					  u8 cmd_verb)
{
	int loopvar = 2000;

	qbman_swp_mc_submit(swp, cmd, cmd_verb);

	do {
		cmd = qbman_swp_mc_result(swp);
	} while (!cmd && loopvar--);

	WARN_ON(!loopvar);

	return cmd;
}