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
typedef  union MEGASAS_REQUEST_DESCRIPTOR_UNION {int dummy; } MEGASAS_REQUEST_DESCRIPTOR_UNION ;
struct megasas_instance {int dummy; } ;
struct megasas_cmd {int dummy; } ;

/* Variables and functions */
 union MEGASAS_REQUEST_DESCRIPTOR_UNION* build_mpt_cmd (struct megasas_instance*,struct megasas_cmd*) ; 
 int /*<<< orphan*/  megasas_fire_cmd_fusion (struct megasas_instance*,union MEGASAS_REQUEST_DESCRIPTOR_UNION*) ; 

__attribute__((used)) static void
megasas_issue_dcmd_fusion(struct megasas_instance *instance,
			  struct megasas_cmd *cmd)
{
	union MEGASAS_REQUEST_DESCRIPTOR_UNION *req_desc;

	req_desc = build_mpt_cmd(instance, cmd);

	megasas_fire_cmd_fusion(instance, req_desc);
	return;
}