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
struct ata_device {int /*<<< orphan*/  tdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_destroy_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ata_tdev_free(struct ata_device *dev)
{
	transport_destroy_device(&dev->tdev);
	put_device(&dev->tdev);
}