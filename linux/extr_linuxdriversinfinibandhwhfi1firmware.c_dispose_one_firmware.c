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
struct firmware_details {int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct firmware_details*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispose_one_firmware(struct firmware_details *fdet)
{
	release_firmware(fdet->fw);
	/* erase all previous information */
	memset(fdet, 0, sizeof(*fdet));
}