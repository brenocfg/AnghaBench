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
struct mantis_pci {int dummy; } ;
struct mantis_ca {struct mantis_pci* ca_priv; } ;
struct dvb_ca_en50221 {struct mantis_ca* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int mantis_hif_read_mem (struct mantis_ca*,int) ; 

__attribute__((used)) static int mantis_ca_read_attr_mem(struct dvb_ca_en50221 *en50221, int slot, int addr)
{
	struct mantis_ca *ca = en50221->data;
	struct mantis_pci *mantis = ca->ca_priv;

	dprintk(MANTIS_DEBUG, 1, "Slot(%d): Request Attribute Mem Read", slot);

	if (slot != 0)
		return -EINVAL;

	return mantis_hif_read_mem(ca, addr);
}