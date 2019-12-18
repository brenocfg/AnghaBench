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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; } ;
struct bfad_port_s {int /*<<< orphan*/  fcs_port; } ;
struct bfad_im_port_s {struct bfad_s* bfad; struct bfad_port_s* port; } ;
struct bfa_rport_qualifier_s {int dummy; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_rport_quals (int /*<<< orphan*/ ,struct bfa_rport_qualifier_s*,int*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct bfa_rport_qualifier_s* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bfa_rport_qualifier_s*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t
bfad_im_num_of_discovered_ports_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_port_s    *port = im_port->port;
	struct bfad_s         *bfad = im_port->bfad;
	int        nrports = 2048;
	struct bfa_rport_qualifier_s *rports = NULL;
	unsigned long   flags;

	rports = kcalloc(nrports, sizeof(struct bfa_rport_qualifier_s),
			 GFP_ATOMIC);
	if (rports == NULL)
		return snprintf(buf, PAGE_SIZE, "Failed\n");

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcs_lport_get_rport_quals(port->fcs_port, rports, &nrports);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	kfree(rports);

	return snprintf(buf, PAGE_SIZE, "%d\n", nrports);
}