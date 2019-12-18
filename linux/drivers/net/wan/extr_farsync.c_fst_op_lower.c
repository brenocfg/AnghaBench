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
struct fst_port_info {size_t index; scalar_t__ run; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 unsigned int FST_RDL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FST_WRL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SETV24O ; 
 int /*<<< orphan*/  fst_issue_cmd (struct fst_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * v24OpSts ; 

__attribute__((used)) static inline void
fst_op_lower(struct fst_port_info *port, unsigned int outputs)
{
	outputs = ~outputs & FST_RDL(port->card, v24OpSts[port->index]);
	FST_WRL(port->card, v24OpSts[port->index], outputs);

	if (port->run)
		fst_issue_cmd(port, SETV24O);
}