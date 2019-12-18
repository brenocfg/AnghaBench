#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct attribute_container {int dummy; } ;
struct TYPE_11__ {struct attribute_container ac; } ;
struct TYPE_12__ {TYPE_4__ target_attrs; } ;
struct spi_internal {TYPE_5__ t; TYPE_3__* f; } ;
struct scsi_target {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct Scsi_Host {TYPE_6__* transportt; } ;
struct TYPE_14__ {int /*<<< orphan*/  class; } ;
struct TYPE_8__ {int /*<<< orphan*/ * class; } ;
struct TYPE_9__ {TYPE_1__ ac; } ;
struct TYPE_13__ {TYPE_2__ host_attrs; } ;
struct TYPE_10__ {scalar_t__ (* deny_binding ) (struct scsi_target*) ;} ;

/* Variables and functions */
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_is_target_device (struct device*) ; 
 TYPE_7__ spi_host_class ; 
 scalar_t__ stub1 (struct scsi_target*) ; 
 struct scsi_target* to_scsi_target (struct device*) ; 
 struct spi_internal* to_spi_internal (TYPE_6__*) ; 

__attribute__((used)) static int spi_target_match(struct attribute_container *cont,
			    struct device *dev)
{
	struct Scsi_Host *shost;
	struct scsi_target *starget;
	struct spi_internal *i;

	if (!scsi_is_target_device(dev))
		return 0;

	shost = dev_to_shost(dev->parent);
	if (!shost->transportt  || shost->transportt->host_attrs.ac.class
	    != &spi_host_class.class)
		return 0;

	i = to_spi_internal(shost->transportt);
	starget = to_scsi_target(dev);

	if (i->f->deny_binding && i->f->deny_binding(starget))
		return 0;

	return &i->t.target_attrs.ac == cont;
}