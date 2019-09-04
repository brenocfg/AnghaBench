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
typedef  scalar_t__ u32 ;
struct octeon_soft_command {int dummy; } ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 

__attribute__((used)) static void lio_sync_octeon_time_cb(struct octeon_device *oct,
				    u32 status, void *buf)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)buf;

	if (status)
		dev_err(&oct->pci_dev->dev,
			"Failed to sync time to octeon; error=%d\n", status);

	octeon_free_soft_command(oct, sc);
}