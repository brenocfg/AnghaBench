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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  altstatus_addr; } ;
struct ata_port {TYPE_1__ ioaddr; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 pata_s3c_check_altstatus(struct ata_port *ap)
{
	return ata_inb(ap->host, ap->ioaddr.altstatus_addr);
}