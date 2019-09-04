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
struct device {int dummy; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int ata_tport_add (struct device*,struct ata_port*) ; 

int ata_sas_tport_add(struct device *parent, struct ata_port *ap)
{
	return ata_tport_add(parent, ap);
}