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
struct fpgaimage {int /*<<< orphan*/  fw_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_1__* firmware_pdev ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int request_firmware (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gs_load_image(struct fpgaimage *fimage, char *fw_file)
{
	int err;

	pr_info("load fpgaimage %s\n", fw_file);

	err = request_firmware(&fimage->fw_entry, fw_file, &firmware_pdev->dev);
	if (err != 0) {
		pr_err("firmware %s is missing, cannot continue.\n", fw_file);
		return err;
	}

	return 0;
}