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
typedef  int /*<<< orphan*/  u32 ;
struct tmComResBusDescr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ResponseRead; int /*<<< orphan*/  ResponseWrite; int /*<<< orphan*/  CommandRead; int /*<<< orphan*/  CommandWrite; int /*<<< orphan*/  ResponseRing; int /*<<< orphan*/  CommandRing; } ;
struct saa7164_dev {TYPE_1__ busdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,TYPE_1__*,...) ; 

__attribute__((used)) static void saa7164_dump_busdesc(struct saa7164_dev *dev)
{
	dprintk(1, "@0x%p busdesc sizeof(struct tmComResBusDescr) = %d bytes\n",
		&dev->busdesc, (u32)sizeof(struct tmComResBusDescr));

	dprintk(1, " .CommandRing   = 0x%016Lx\n", dev->busdesc.CommandRing);
	dprintk(1, " .ResponseRing  = 0x%016Lx\n", dev->busdesc.ResponseRing);
	dprintk(1, " .CommandWrite  = 0x%x\n", dev->busdesc.CommandWrite);
	dprintk(1, " .CommandRead   = 0x%x\n", dev->busdesc.CommandRead);
	dprintk(1, " .ResponseWrite = 0x%x\n", dev->busdesc.ResponseWrite);
	dprintk(1, " .ResponseRead  = 0x%x\n", dev->busdesc.ResponseRead);
}