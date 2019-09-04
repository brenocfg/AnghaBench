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
struct zpodd {int zp_ready; } ;
struct ata_device {struct zpodd* zpodd; } ;

/* Variables and functions */

bool zpodd_zpready(struct ata_device *dev)
{
	struct zpodd *zpodd = dev->zpodd;
	return zpodd->zp_ready;
}