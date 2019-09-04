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
struct sev_data_decommission {unsigned int handle; } ;
struct sev_data_deactivate {unsigned int handle; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct sev_data_decommission*) ; 
 struct sev_data_decommission* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sev_guest_deactivate (struct sev_data_decommission*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sev_guest_decommission (struct sev_data_decommission*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sev_guest_df_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbinvd_on_all_cpus () ; 

__attribute__((used)) static void sev_unbind_asid(struct kvm *kvm, unsigned int handle)
{
	struct sev_data_decommission *decommission;
	struct sev_data_deactivate *data;

	if (!handle)
		return;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return;

	/* deactivate handle */
	data->handle = handle;
	sev_guest_deactivate(data, NULL);

	wbinvd_on_all_cpus();
	sev_guest_df_flush(NULL);
	kfree(data);

	decommission = kzalloc(sizeof(*decommission), GFP_KERNEL);
	if (!decommission)
		return;

	/* decommission handle */
	decommission->handle = handle;
	sev_guest_decommission(decommission, NULL);

	kfree(decommission);
}