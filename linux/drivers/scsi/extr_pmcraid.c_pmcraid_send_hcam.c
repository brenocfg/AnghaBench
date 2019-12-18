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
struct pmcraid_instance {int dummy; } ;
struct pmcraid_cmd {int dummy; } ;

/* Variables and functions */
 struct pmcraid_cmd* pmcraid_init_hcam (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_send_hcam_cmd (struct pmcraid_cmd*) ; 

__attribute__((used)) static void pmcraid_send_hcam(struct pmcraid_instance *pinstance, u8 type)
{
	struct pmcraid_cmd *cmd = pmcraid_init_hcam(pinstance, type);
	pmcraid_send_hcam_cmd(cmd);
}