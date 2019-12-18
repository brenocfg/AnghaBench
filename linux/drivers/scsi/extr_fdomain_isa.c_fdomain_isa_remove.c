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
struct device {int dummy; } ;
struct Scsi_Host {int io_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDOMAIN_REGION_SIZE ; 
 struct Scsi_Host* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdomain_destroy (struct Scsi_Host*) ; 
 int /*<<< orphan*/  release_region (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdomain_isa_remove(struct device *dev, unsigned int ndev)
{
	struct Scsi_Host *sh = dev_get_drvdata(dev);
	int base = sh->io_port;

	fdomain_destroy(sh);
	release_region(base, FDOMAIN_REGION_SIZE);
	dev_set_drvdata(dev, NULL);
	return 0;
}