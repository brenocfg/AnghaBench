#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct attribute_container {int dummy; } ;
struct TYPE_3__ {struct attribute_container ac; } ;
struct TYPE_4__ {TYPE_1__ host_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_is_port (struct device*) ; 
 TYPE_2__* ata_scsi_transport_template ; 

__attribute__((used)) static int ata_tport_match(struct attribute_container *cont,
			   struct device *dev)
{
	if (!ata_is_port(dev))
		return 0;
	return &ata_scsi_transport_template->host_attrs.ac == cont;
}