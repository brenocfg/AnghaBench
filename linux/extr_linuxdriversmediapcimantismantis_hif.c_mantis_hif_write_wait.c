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
typedef  int u32 ;
struct mantis_pci {int gpif_status; int /*<<< orphan*/  num; } ;
struct mantis_ca {int /*<<< orphan*/  hif_write_wq; struct mantis_pci* ca_priv; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  ERESTARTSYS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  MANTIS_GPIF_STATUS ; 
 int MANTIS_GPIF_WRACK ; 
 int MANTIS_SBUF_OPDONE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int mmread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mantis_hif_write_wait(struct mantis_ca *ca)
{
	struct mantis_pci *mantis = ca->ca_priv;
	u32 opdone = 0, timeout = 0;
	int rc = 0;

	if (wait_event_timeout(ca->hif_write_wq,
			       mantis->gpif_status & MANTIS_GPIF_WRACK,
			       msecs_to_jiffies(500)) == -ERESTARTSYS) {

		dprintk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): Write ACK timed out !", mantis->num);
		rc = -EREMOTEIO;
	}
	dprintk(MANTIS_DEBUG, 1, "Write Acknowledged");
	mantis->gpif_status &= ~MANTIS_GPIF_WRACK;
	while (!opdone) {
		opdone = (mmread(MANTIS_GPIF_STATUS) & MANTIS_SBUF_OPDONE);
		udelay(500);
		timeout++;
		if (timeout > 100) {
			dprintk(MANTIS_ERROR, 1, "Adapter(%d) Slot(0): Write operation timed out!", mantis->num);
			rc = -ETIMEDOUT;
			break;
		}
	}
	dprintk(MANTIS_DEBUG, 1, "HIF Write success");
	return rc;
}