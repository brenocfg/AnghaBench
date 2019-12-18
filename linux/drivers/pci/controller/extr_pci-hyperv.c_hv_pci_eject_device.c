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
struct hv_pci_dev {int /*<<< orphan*/  wrk; TYPE_1__* hbus; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hvpcibus (TYPE_1__*) ; 
 int /*<<< orphan*/  get_pcichild (struct hv_pci_dev*) ; 
 int /*<<< orphan*/  hv_eject_device_work ; 
 int /*<<< orphan*/  hv_pcichild_ejecting ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hv_pci_eject_device(struct hv_pci_dev *hpdev)
{
	hpdev->state = hv_pcichild_ejecting;
	get_pcichild(hpdev);
	INIT_WORK(&hpdev->wrk, hv_eject_device_work);
	get_hvpcibus(hpdev->hbus);
	queue_work(hpdev->hbus->wq, &hpdev->wrk);
}