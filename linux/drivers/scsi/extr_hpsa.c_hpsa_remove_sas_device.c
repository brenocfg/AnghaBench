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
struct hpsa_scsi_dev_t {int /*<<< orphan*/ * sas_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpsa_free_sas_port (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpsa_remove_sas_device(struct hpsa_scsi_dev_t *device)
{
	if (device->sas_port) {
		hpsa_free_sas_port(device->sas_port);
		device->sas_port = NULL;
	}
}