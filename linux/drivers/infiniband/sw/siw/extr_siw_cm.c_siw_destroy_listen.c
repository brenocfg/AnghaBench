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
struct iw_cm_id {int /*<<< orphan*/ * provider_data; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siw_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  siw_drop_listeners (struct iw_cm_id*) ; 

int siw_destroy_listen(struct iw_cm_id *id)
{
	if (!id->provider_data) {
		siw_dbg(id->device, "no cep(s)\n");
		return 0;
	}
	siw_drop_listeners(id);
	kfree(id->provider_data);
	id->provider_data = NULL;

	return 0;
}