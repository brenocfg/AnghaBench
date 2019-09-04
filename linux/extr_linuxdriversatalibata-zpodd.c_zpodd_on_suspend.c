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
struct zpodd {int zp_sampled; int zp_ready; unsigned long last_ready; } ;
struct ata_device {struct zpodd* zpodd; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int zpodd_poweroff_delay ; 
 int /*<<< orphan*/  zpready (struct ata_device*) ; 

void zpodd_on_suspend(struct ata_device *dev)
{
	struct zpodd *zpodd = dev->zpodd;
	unsigned long expires;

	if (!zpready(dev)) {
		zpodd->zp_sampled = false;
		zpodd->zp_ready = false;
		return;
	}

	if (!zpodd->zp_sampled) {
		zpodd->zp_sampled = true;
		zpodd->last_ready = jiffies;
		return;
	}

	expires = zpodd->last_ready +
		  msecs_to_jiffies(zpodd_poweroff_delay * 1000);
	if (time_before(jiffies, expires))
		return;

	zpodd->zp_ready = true;
}