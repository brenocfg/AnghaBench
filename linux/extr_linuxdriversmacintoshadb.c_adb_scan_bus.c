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
struct adb_request {int reply_len; int /*<<< orphan*/ * reply; } ;
struct TYPE_2__ {int original_address; int /*<<< orphan*/  handler_id; } ;

/* Variables and functions */
 int ADBREQ_REPLY ; 
 int ADBREQ_SYNC ; 
 TYPE_1__* adb_handler ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int,int,int,...) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int adb_scan_bus(void)
{
	int i, highFree=0, noMovement;
	int devmask = 0;
	struct adb_request req;
	
	/* assumes adb_handler[] is all zeroes at this point */
	for (i = 1; i < 16; i++) {
		/* see if there is anything at address i */
		adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
                            (i << 4) | 0xf);
		if (req.reply_len > 1)
			/* one or more devices at this address */
			adb_handler[i].original_address = i;
		else if (i > highFree)
			highFree = i;
	}

	/* Note we reset noMovement to 0 each time we move a device */
	for (noMovement = 1; noMovement < 2 && highFree > 0; noMovement++) {
		for (i = 1; i < 16; i++) {
			if (adb_handler[i].original_address == 0)
				continue;
			/*
			 * Send a "talk register 3" command to address i
			 * to provoke a collision if there is more than
			 * one device at this address.
			 */
			adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    (i << 4) | 0xf);
			/*
			 * Move the device(s) which didn't detect a
			 * collision to address `highFree'.  Hopefully
			 * this only moves one device.
			 */
			adb_request(&req, NULL, ADBREQ_SYNC, 3,
				    (i<< 4) | 0xb, (highFree | 0x60), 0xfe);
			/*
			 * See if anybody actually moved. This is suggested
			 * by HW TechNote 01:
			 *
			 * http://developer.apple.com/technotes/hw/hw_01.html
			 */
			adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    (highFree << 4) | 0xf);
			if (req.reply_len <= 1) continue;
			/*
			 * Test whether there are any device(s) left
			 * at address i.
			 */
			adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
				    (i << 4) | 0xf);
			if (req.reply_len > 1) {
				/*
				 * There are still one or more devices
				 * left at address i.  Register the one(s)
				 * we moved to `highFree', and find a new
				 * value for highFree.
				 */
				adb_handler[highFree].original_address =
					adb_handler[i].original_address;
				while (highFree > 0 &&
				       adb_handler[highFree].original_address)
					highFree--;
				if (highFree <= 0)
					break;

				noMovement = 0;
			} else {
				/*
				 * No devices left at address i; move the
				 * one(s) we moved to `highFree' back to i.
				 */
				adb_request(&req, NULL, ADBREQ_SYNC, 3,
					    (highFree << 4) | 0xb,
					    (i | 0x60), 0xfe);
			}
		}	
	}

	/* Now fill in the handler_id field of the adb_handler entries. */
	pr_debug("adb devices:\n");
	for (i = 1; i < 16; i++) {
		if (adb_handler[i].original_address == 0)
			continue;
		adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
			    (i << 4) | 0xf);
		adb_handler[i].handler_id = req.reply[2];
		pr_debug(" [%d]: %d %x\n", i, adb_handler[i].original_address,
			 adb_handler[i].handler_id);
		devmask |= 1 << i;
	}
	return devmask;
}