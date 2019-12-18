#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ssb_sprom {void* revision; } ;
struct TYPE_6__ {int status; TYPE_2__* dev; } ;
struct ssb_bus {int chip_id; void* sprom_size; void* sprom_offset; TYPE_3__ chipco; } ;
struct TYPE_4__ {int revision; } ;
struct TYPE_5__ {TYPE_1__ id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* SSB_SPROMSIZE_WORDS_R123 ; 
 void* SSB_SPROMSIZE_WORDS_R4 ; 
 void* SSB_SPROM_BASE1 ; 
 void* SSB_SPROM_BASE31 ; 
 int /*<<< orphan*/ * kcalloc (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int sprom_check_crc (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sprom_do_read (struct ssb_bus*,int /*<<< orphan*/ *) ; 
 int sprom_extract (struct ssb_bus*,struct ssb_sprom*,int /*<<< orphan*/ *,void*) ; 
 int ssb_fill_sprom_with_fallback (struct ssb_bus*,struct ssb_sprom*) ; 
 int /*<<< orphan*/  ssb_is_sprom_available (struct ssb_bus*) ; 

__attribute__((used)) static int ssb_pci_sprom_get(struct ssb_bus *bus,
			     struct ssb_sprom *sprom)
{
	int err;
	u16 *buf;

	if (!ssb_is_sprom_available(bus)) {
		pr_err("No SPROM available!\n");
		return -ENODEV;
	}
	if (bus->chipco.dev) {	/* can be unavailable! */
		/*
		 * get SPROM offset: SSB_SPROM_BASE1 except for
		 * chipcommon rev >= 31 or chip ID is 0x4312 and
		 * chipcommon status & 3 == 2
		 */
		if (bus->chipco.dev->id.revision >= 31)
			bus->sprom_offset = SSB_SPROM_BASE31;
		else if (bus->chip_id == 0x4312 &&
			 (bus->chipco.status & 0x03) == 2)
			bus->sprom_offset = SSB_SPROM_BASE31;
		else
			bus->sprom_offset = SSB_SPROM_BASE1;
	} else {
		bus->sprom_offset = SSB_SPROM_BASE1;
	}
	pr_debug("SPROM offset is 0x%x\n", bus->sprom_offset);

	buf = kcalloc(SSB_SPROMSIZE_WORDS_R123, sizeof(u16), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	bus->sprom_size = SSB_SPROMSIZE_WORDS_R123;
	sprom_do_read(bus, buf);
	err = sprom_check_crc(buf, bus->sprom_size);
	if (err) {
		/* try for a 440 byte SPROM - revision 4 and higher */
		kfree(buf);
		buf = kcalloc(SSB_SPROMSIZE_WORDS_R4, sizeof(u16),
			      GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
		bus->sprom_size = SSB_SPROMSIZE_WORDS_R4;
		sprom_do_read(bus, buf);
		err = sprom_check_crc(buf, bus->sprom_size);
		if (err) {
			/* All CRC attempts failed.
			 * Maybe there is no SPROM on the device?
			 * Now we ask the arch code if there is some sprom
			 * available for this device in some other storage */
			err = ssb_fill_sprom_with_fallback(bus, sprom);
			if (err) {
				pr_warn("WARNING: Using fallback SPROM failed (err %d)\n",
					err);
				goto out_free;
			} else {
				pr_debug("Using SPROM revision %d provided by platform\n",
					 sprom->revision);
				err = 0;
				goto out_free;
			}
			pr_warn("WARNING: Invalid SPROM CRC (corrupt SPROM)\n");
		}
	}
	err = sprom_extract(bus, sprom, buf, bus->sprom_size);

out_free:
	kfree(buf);
	return err;
}