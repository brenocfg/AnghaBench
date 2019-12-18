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
struct atp {TYPE_1__* intf; int /*<<< orphan*/ * info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ atp_geyser_init (struct atp*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fountain_info ; 

__attribute__((used)) static int atp_handle_geyser(struct atp *dev)
{
	if (dev->info != &fountain_info) {
		/* switch to raw sensor mode */
		if (atp_geyser_init(dev))
			return -EIO;

		dev_info(&dev->intf->dev, "Geyser mode initialized.\n");
	}

	return 0;
}