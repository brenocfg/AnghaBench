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
struct fw_request {int timedout; int /*<<< orphan*/  firmware_id; int /*<<< orphan*/  release_timeout_j; struct fw_download* fw_download; } ;
struct fw_download {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_firmware (struct fw_download*,struct fw_request*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exceeds_release_timeout(struct fw_request *fw_req)
{
	struct fw_download *fw_download = fw_req->fw_download;

	if (time_before(jiffies, fw_req->release_timeout_j))
		return 0;

	dev_err(fw_download->parent,
		"Firmware download didn't finish in time, abort: %d\n",
		fw_req->firmware_id);

	fw_req->timedout = true;
	free_firmware(fw_download, fw_req);

	return -ETIMEDOUT;
}