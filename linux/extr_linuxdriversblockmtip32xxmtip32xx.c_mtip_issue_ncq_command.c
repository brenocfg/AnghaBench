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
struct mtip_port {int /*<<< orphan*/ * cmd_issue_lock; int /*<<< orphan*/ * cmd_issue; int /*<<< orphan*/ * s_active; } ;

/* Variables and functions */
 int MTIP_TAG_BIT (int) ; 
 size_t MTIP_TAG_INDEX (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mtip_issue_ncq_command(struct mtip_port *port, int tag)
{
	int group = tag >> 5;

	/* guard SACT and CI registers */
	spin_lock(&port->cmd_issue_lock[group]);
	writel((1 << MTIP_TAG_BIT(tag)),
			port->s_active[MTIP_TAG_INDEX(tag)]);
	writel((1 << MTIP_TAG_BIT(tag)),
			port->cmd_issue[MTIP_TAG_INDEX(tag)]);
	spin_unlock(&port->cmd_issue_lock[group]);
}