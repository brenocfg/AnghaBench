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
struct slic_device {int /*<<< orphan*/  link_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  slic_configure_link_locked (struct slic_device*,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slic_configure_link(struct slic_device *sdev, int speed,
				unsigned int duplex)
{
	spin_lock_bh(&sdev->link_lock);
	slic_configure_link_locked(sdev, speed, duplex);
	spin_unlock_bh(&sdev->link_lock);
}