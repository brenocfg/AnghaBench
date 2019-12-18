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
struct hinfc_host {scalar_t__ command; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long HINFC504_NFC_TIMEOUT ; 
 int HINFC504_READY ; 
 int /*<<< orphan*/  HINFC504_STATUS ; 
 scalar_t__ NAND_CMD_ERASE2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hinfc_read (struct hinfc_host*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void wait_controller_finished(struct hinfc_host *host)
{
	unsigned long timeout = jiffies + HINFC504_NFC_TIMEOUT;
	int val;

	while (time_before(jiffies, timeout)) {
		val = hinfc_read(host, HINFC504_STATUS);
		if (host->command == NAND_CMD_ERASE2) {
			/* nfc is ready */
			while (!(val & HINFC504_READY))	{
				usleep_range(500, 1000);
				val = hinfc_read(host, HINFC504_STATUS);
			}
			return;
		}

		if (val & HINFC504_READY)
			return;
	}

	/* wait cmd timeout */
	dev_err(host->dev, "Wait NAND controller exec cmd timeout.\n");
}