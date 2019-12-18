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
struct adb_request {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  macii_poll () ; 
 int macii_write (struct adb_request*) ; 

__attribute__((used)) static int macii_send_request(struct adb_request *req, int sync)
{
	int err;

	err = macii_write(req);
	if (err)
		return err;

	if (sync)
		while (!req->complete)
			macii_poll();

	return 0;
}