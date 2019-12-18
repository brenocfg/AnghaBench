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
struct mantis_pci {int /*<<< orphan*/  num; } ;
struct mantis_ca {int hif_event; int /*<<< orphan*/  hif_opdone_wq; struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int MANTIS_SBUF_OPDONE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mantis_hif_sbuf_opdone_wait(struct mantis_ca *ca)
{
	struct mantis_pci *mantis = ca->ca_priv;
	int rc = 0;

	if (wait_event_timeout(ca->hif_opdone_wq,
			       ca->hif_event & MANTIS_SBUF_OPDONE,
			       msecs_to_jiffies(500)) == -ERESTARTSYS) {

		dprintk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): Smart buffer operation timeout !", mantis->num);
		rc = -EREMOTEIO;
	}
	dprintk(MANTIS_DEBUG, 1, "Smart Buffer Operation complete");
	ca->hif_event &= ~MANTIS_SBUF_OPDONE;
	return rc;
}