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
struct guc_process_desc {int dummy; } ;

/* Variables and functions */
 struct guc_process_desc* __get_process_desc (struct intel_guc_client*) ; 
 int /*<<< orphan*/  memset (struct guc_process_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void guc_proc_desc_fini(struct intel_guc_client *client)
{
	struct guc_process_desc *desc;

	desc = __get_process_desc(client);
	memset(desc, 0, sizeof(*desc));
}