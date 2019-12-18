#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct st_hba {TYPE_3__* pdev; struct st_frame* copy_buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  build; int /*<<< orphan*/  oem; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct st_frame {int id; int subid; int /*<<< orphan*/  irq_vec; scalar_t__ irq_level; int /*<<< orphan*/  slot; int /*<<< orphan*/  bus; TYPE_1__ drv_ver; scalar_t__ rom_addr; scalar_t__ base; } ;
struct st_ccb {int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {int vendor; int device; int subsystem_vendor; int subsystem_device; int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_BUILD_VER ; 
 int /*<<< orphan*/  ST_OEM ; 
 int /*<<< orphan*/  ST_VER_MAJOR ; 
 int /*<<< orphan*/  ST_VER_MINOR ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 unsigned long pci_resource_start (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (int /*<<< orphan*/ ,struct st_frame*,size_t) ; 
 int /*<<< orphan*/  scsi_sg_copy_to_buffer (int /*<<< orphan*/ ,struct st_frame*,size_t) ; 

__attribute__((used)) static void stex_controller_info(struct st_hba *hba, struct st_ccb *ccb)
{
	struct st_frame *p;
	size_t count = sizeof(struct st_frame);

	p = hba->copy_buffer;
	scsi_sg_copy_to_buffer(ccb->cmd, p, count);
	memset(p->base, 0, sizeof(u32)*6);
	*(unsigned long *)(p->base) = pci_resource_start(hba->pdev, 0);
	p->rom_addr = 0;

	p->drv_ver.major = ST_VER_MAJOR;
	p->drv_ver.minor = ST_VER_MINOR;
	p->drv_ver.oem = ST_OEM;
	p->drv_ver.build = ST_BUILD_VER;

	p->bus = hba->pdev->bus->number;
	p->slot = hba->pdev->devfn;
	p->irq_level = 0;
	p->irq_vec = hba->pdev->irq;
	p->id = hba->pdev->vendor << 16 | hba->pdev->device;
	p->subid =
		hba->pdev->subsystem_vendor << 16 | hba->pdev->subsystem_device;

	scsi_sg_copy_from_buffer(ccb->cmd, p, count);
}