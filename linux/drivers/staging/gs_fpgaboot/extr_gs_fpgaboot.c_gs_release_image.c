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
struct fpgaimage {int /*<<< orphan*/  fw_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gs_release_image(struct fpgaimage *fimage)
{
	release_firmware(fimage->fw_entry);
	pr_info("release fpgaimage\n");

	return 0;
}