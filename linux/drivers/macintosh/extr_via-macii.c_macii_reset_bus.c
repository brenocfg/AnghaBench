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
struct adb_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADBREQ_NOSEND ; 
 int /*<<< orphan*/  ADB_BUSRESET ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macii_send_request (struct adb_request*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int macii_reset_bus(void)
{
	static struct adb_request req;

	/* Command = 0, Address = ignored */
	adb_request(&req, NULL, ADBREQ_NOSEND, 1, ADB_BUSRESET);
	macii_send_request(&req, 1);

	/* Don't want any more requests during the Global Reset low time. */
	udelay(3000);

	return 0;
}