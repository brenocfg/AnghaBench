#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_transport_template {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_attrs; } ;
struct ata_internal {int /*<<< orphan*/  dev_attr_cont; int /*<<< orphan*/  link_attr_cont; TYPE_1__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ata_internal*) ; 
 struct ata_internal* to_ata_internal (struct scsi_transport_template*) ; 
 int /*<<< orphan*/  transport_container_unregister (int /*<<< orphan*/ *) ; 

void ata_release_transport(struct scsi_transport_template *t)
{
	struct ata_internal *i = to_ata_internal(t);

	transport_container_unregister(&i->t.host_attrs);
	transport_container_unregister(&i->link_attr_cont);
	transport_container_unregister(&i->dev_attr_cont);

	kfree(i);
}