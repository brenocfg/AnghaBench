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
struct fw_blob {int /*<<< orphan*/  fw; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fw_blob* qla_fw_blobs ; 
 int /*<<< orphan*/  qla_fw_lock ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla2x00_release_firmware(void)
{
	struct fw_blob *blob;

	mutex_lock(&qla_fw_lock);
	for (blob = qla_fw_blobs; blob->name; blob++)
		release_firmware(blob->fw);
	mutex_unlock(&qla_fw_lock);
}