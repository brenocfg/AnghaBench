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
struct device {scalar_t__ release; } ;

/* Variables and functions */
 scalar_t__ ata_tport_release ; 

__attribute__((used)) static int ata_is_port(const struct device *dev)
{
	return dev->release == ata_tport_release;
}