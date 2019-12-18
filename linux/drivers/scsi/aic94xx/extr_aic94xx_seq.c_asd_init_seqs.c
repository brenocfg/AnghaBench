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
struct asd_ha_struct {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_RAZOR_SEQUENCER_FW_FILE ; 
 int /*<<< orphan*/  asd_printk (char*,int /*<<< orphan*/ ,...) ; 
 int asd_request_firmware (struct asd_ha_struct*) ; 
 int asd_seq_download_seqs (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  asd_seq_setup_seqs (struct asd_ha_struct*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 

int asd_init_seqs(struct asd_ha_struct *asd_ha)
{
	int err;

	err = asd_request_firmware(asd_ha);

	if (err) {
		asd_printk("Failed to load sequencer firmware file %s, error %d\n",
			   SAS_RAZOR_SEQUENCER_FW_FILE, err);
		return err;
	}

	err = asd_seq_download_seqs(asd_ha);
	if (err) {
		asd_printk("couldn't download sequencers for %s\n",
			   pci_name(asd_ha->pcidev));
		return err;
	}

	asd_seq_setup_seqs(asd_ha);

	return 0;
}