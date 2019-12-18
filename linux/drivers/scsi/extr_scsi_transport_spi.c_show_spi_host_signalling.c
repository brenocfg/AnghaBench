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
struct spi_internal {TYPE_1__* f; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_signalling ) (struct Scsi_Host*) ;} ;

/* Variables and functions */
 char* spi_signal_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_signalling (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct Scsi_Host*) ; 
 struct spi_internal* to_spi_internal (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* transport_class_to_shost (struct device*) ; 

__attribute__((used)) static ssize_t show_spi_host_signalling(struct device *cdev,
					struct device_attribute *attr,
					char *buf)
{
	struct Scsi_Host *shost = transport_class_to_shost(cdev);
	struct spi_internal *i = to_spi_internal(shost->transportt);

	if (i->f->get_signalling)
		i->f->get_signalling(shost);

	return sprintf(buf, "%s\n", spi_signal_to_string(spi_signalling(shost)));
}