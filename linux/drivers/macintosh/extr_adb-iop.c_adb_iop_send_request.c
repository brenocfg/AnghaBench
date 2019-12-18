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
 int /*<<< orphan*/  adb_iop_poll () ; 
 int adb_iop_write (struct adb_request*) ; 

int adb_iop_send_request(struct adb_request *req, int sync)
{
	int err;

	err = adb_iop_write(req);
	if (err)
		return err;

	if (sync) {
		while (!req->complete)
			adb_iop_poll();
	}
	return 0;
}