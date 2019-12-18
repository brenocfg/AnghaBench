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
typedef  int u32 ;
struct flash_desc {int member_0; int member_1; int vendor_and_model_id; unsigned int size_mb; } ;
struct TYPE_2__ {unsigned int sf_size; unsigned int sf_nsec; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct flash_desc*) ; 
 unsigned int FLASH_MIN_SIZE ; 
 int /*<<< orphan*/  SF_OP_A ; 
 int /*<<< orphan*/  SF_RD_ID ; 
 unsigned int SF_SEC_SIZE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,...) ; 
 int sf1_read (struct adapter*,int,int /*<<< orphan*/ ,int,int*) ; 
 int sf1_write (struct adapter*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t4_get_flash_params(struct adapter *adap)
{
	/* Table for non-Numonix supported flash parts.  Numonix parts are left
	 * to the preexisting code.  All flash parts have 64KB sectors.
	 */
	static struct flash_desc supported_flash[] = {
		{ 0x150201, 4 << 20 },       /* Spansion 4MB S25FL032P */
	};

	unsigned int part, manufacturer;
	unsigned int density, size = 0;
	u32 flashid = 0;
	int ret;

	/* Issue a Read ID Command to the Flash part.  We decode supported
	 * Flash parts and their sizes from this.  There's a newer Query
	 * Command which can retrieve detailed geometry information but many
	 * Flash parts don't support it.
	 */

	ret = sf1_write(adap, 1, 1, 0, SF_RD_ID);
	if (!ret)
		ret = sf1_read(adap, 3, 0, 1, &flashid);
	t4_write_reg(adap, SF_OP_A, 0);                    /* unlock SF */
	if (ret)
		return ret;

	/* Check to see if it's one of our non-standard supported Flash parts.
	 */
	for (part = 0; part < ARRAY_SIZE(supported_flash); part++)
		if (supported_flash[part].vendor_and_model_id == flashid) {
			adap->params.sf_size = supported_flash[part].size_mb;
			adap->params.sf_nsec =
				adap->params.sf_size / SF_SEC_SIZE;
			goto found;
		}

	/* Decode Flash part size.  The code below looks repetitive with
	 * common encodings, but that's not guaranteed in the JEDEC
	 * specification for the Read JEDEC ID command.  The only thing that
	 * we're guaranteed by the JEDEC specification is where the
	 * Manufacturer ID is in the returned result.  After that each
	 * Manufacturer ~could~ encode things completely differently.
	 * Note, all Flash parts must have 64KB sectors.
	 */
	manufacturer = flashid & 0xff;
	switch (manufacturer) {
	case 0x20: { /* Micron/Numonix */
		/* This Density -> Size decoding table is taken from Micron
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x14: /* 1MB */
			size = 1 << 20;
			break;
		case 0x15: /* 2MB */
			size = 1 << 21;
			break;
		case 0x16: /* 4MB */
			size = 1 << 22;
			break;
		case 0x17: /* 8MB */
			size = 1 << 23;
			break;
		case 0x18: /* 16MB */
			size = 1 << 24;
			break;
		case 0x19: /* 32MB */
			size = 1 << 25;
			break;
		case 0x20: /* 64MB */
			size = 1 << 26;
			break;
		case 0x21: /* 128MB */
			size = 1 << 27;
			break;
		case 0x22: /* 256MB */
			size = 1 << 28;
			break;
		}
		break;
	}
	case 0x9d: { /* ISSI -- Integrated Silicon Solution, Inc. */
		/* This Density -> Size decoding table is taken from ISSI
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x16: /* 32 MB */
			size = 1 << 25;
			break;
		case 0x17: /* 64MB */
			size = 1 << 26;
			break;
		}
		break;
	}
	case 0xc2: { /* Macronix */
		/* This Density -> Size decoding table is taken from Macronix
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x17: /* 8MB */
			size = 1 << 23;
			break;
		case 0x18: /* 16MB */
			size = 1 << 24;
			break;
		}
		break;
	}
	case 0xef: { /* Winbond */
		/* This Density -> Size decoding table is taken from Winbond
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x17: /* 8MB */
			size = 1 << 23;
			break;
		case 0x18: /* 16MB */
			size = 1 << 24;
			break;
		}
		break;
	}
	}

	/* If we didn't recognize the FLASH part, that's no real issue: the
	 * Hardware/Software contract says that Hardware will _*ALWAYS*_
	 * use a FLASH part which is at least 4MB in size and has 64KB
	 * sectors.  The unrecognized FLASH part is likely to be much larger
	 * than 4MB, but that's all we really need.
	 */
	if (size == 0) {
		dev_warn(adap->pdev_dev, "Unknown Flash Part, ID = %#x, assuming 4MB\n",
			 flashid);
		size = 1 << 22;
	}

	/* Store decoded Flash size and fall through into vetting code. */
	adap->params.sf_size = size;
	adap->params.sf_nsec = size / SF_SEC_SIZE;

found:
	if (adap->params.sf_size < FLASH_MIN_SIZE)
		dev_warn(adap->pdev_dev, "WARNING: Flash Part ID %#x, size %#x < %#x\n",
			 flashid, adap->params.sf_size, FLASH_MIN_SIZE);
	return 0;
}