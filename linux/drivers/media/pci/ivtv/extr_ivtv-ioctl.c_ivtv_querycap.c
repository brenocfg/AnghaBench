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
struct v4l2_capability {int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int v4l2_cap; int /*<<< orphan*/  pdev; int /*<<< orphan*/  card_name; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DRIVER_NAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ivtv_querycap(struct file *file, void *fh, struct v4l2_capability *vcap)
{
	struct ivtv_open_id *id = fh2id(file->private_data);
	struct ivtv *itv = id->itv;

	strscpy(vcap->driver, IVTV_DRIVER_NAME, sizeof(vcap->driver));
	strscpy(vcap->card, itv->card_name, sizeof(vcap->card));
	snprintf(vcap->bus_info, sizeof(vcap->bus_info), "PCI:%s", pci_name(itv->pdev));
	vcap->capabilities = itv->v4l2_cap | V4L2_CAP_DEVICE_CAPS;
	return 0;
}