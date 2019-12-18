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
struct intel_guc_client {int dummy; } ;

/* Variables and functions */
 int create_doorbell (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_proc_desc_fini (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_proc_desc_init (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_stage_desc_fini (struct intel_guc_client*) ; 
 int /*<<< orphan*/  guc_stage_desc_init (struct intel_guc_client*) ; 

__attribute__((used)) static int __guc_client_enable(struct intel_guc_client *client)
{
	int ret;

	guc_proc_desc_init(client);
	guc_stage_desc_init(client);

	ret = create_doorbell(client);
	if (ret)
		goto fail;

	return 0;

fail:
	guc_stage_desc_fini(client);
	guc_proc_desc_fini(client);
	return ret;
}