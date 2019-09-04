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
struct mtip_port {int /*<<< orphan*/ * cmd_issue; } ;

/* Variables and functions */
 int MTIP_TAG_BIT (int) ; 
 size_t MTIP_TAG_INDEX (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtip_issue_non_ncq_command(struct mtip_port *port, int tag)
{
	writel(1 << MTIP_TAG_BIT(tag), port->cmd_issue[MTIP_TAG_INDEX(tag)]);
}