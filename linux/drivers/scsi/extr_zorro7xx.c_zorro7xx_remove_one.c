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
struct zorro_dev {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  irq; } ;
struct NCR_700_Host_Parameters {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCR_700_release (struct Scsi_Host*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  kfree (struct NCR_700_Host_Parameters*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct NCR_700_Host_Parameters* shost_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* zorro_get_drvdata (struct zorro_dev*) ; 
 int /*<<< orphan*/  zorro_release_device (struct zorro_dev*) ; 

__attribute__((used)) static void zorro7xx_remove_one(struct zorro_dev *z)
{
	struct Scsi_Host *host = zorro_get_drvdata(z);
	struct NCR_700_Host_Parameters *hostdata = shost_priv(host);

	scsi_remove_host(host);

	NCR_700_release(host);
	kfree(hostdata);
	free_irq(host->irq, host);
	zorro_release_device(z);
}