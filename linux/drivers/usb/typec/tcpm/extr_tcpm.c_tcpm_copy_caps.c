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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  type; int /*<<< orphan*/  prefer_role; } ;
struct tcpm_port {int /*<<< orphan*/  self_powered; TYPE_1__ typec_caps; int /*<<< orphan*/  operating_snk_mw; int /*<<< orphan*/  snk_vdo; int /*<<< orphan*/  nr_snk_vdo; int /*<<< orphan*/  snk_pdo; void* nr_snk_pdo; int /*<<< orphan*/  src_pdo; void* nr_src_pdo; } ;
struct tcpc_config {int /*<<< orphan*/  self_powered; int /*<<< orphan*/  data; int /*<<< orphan*/  type; int /*<<< orphan*/  default_role; int /*<<< orphan*/  operating_snk_mw; int /*<<< orphan*/  nr_snk_vdo; int /*<<< orphan*/  snk_vdo; int /*<<< orphan*/  nr_snk_pdo; int /*<<< orphan*/  snk_pdo; int /*<<< orphan*/  nr_src_pdo; int /*<<< orphan*/  src_pdo; } ;

/* Variables and functions */
 int EINVAL ; 
 void* tcpm_copy_pdos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpm_copy_vdos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcpm_validate_caps (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_copy_caps(struct tcpm_port *port,
			  const struct tcpc_config *tcfg)
{
	if (tcpm_validate_caps(port, tcfg->src_pdo, tcfg->nr_src_pdo) ||
	    tcpm_validate_caps(port, tcfg->snk_pdo, tcfg->nr_snk_pdo))
		return -EINVAL;

	port->nr_src_pdo = tcpm_copy_pdos(port->src_pdo, tcfg->src_pdo,
					  tcfg->nr_src_pdo);
	port->nr_snk_pdo = tcpm_copy_pdos(port->snk_pdo, tcfg->snk_pdo,
					  tcfg->nr_snk_pdo);

	port->nr_snk_vdo = tcpm_copy_vdos(port->snk_vdo, tcfg->snk_vdo,
					  tcfg->nr_snk_vdo);

	port->operating_snk_mw = tcfg->operating_snk_mw;

	port->typec_caps.prefer_role = tcfg->default_role;
	port->typec_caps.type = tcfg->type;
	port->typec_caps.data = tcfg->data;
	port->self_powered = tcfg->self_powered;

	return 0;
}