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
struct v4l2_capability {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  device_caps; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct cx18_stream {int /*<<< orphan*/  v4l2_dev_caps; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  v4l2_cap; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  card_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DRIVER_NAME ; 
 int /*<<< orphan*/  V4L2_CAP_DEVICE_CAPS ; 
 struct cx18_open_id* fh2id (void*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cx18_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cx18_querycap(struct file *file, void *fh,
				struct v4l2_capability *vcap)
{
	struct cx18_open_id *id = fh2id(fh);
	struct cx18_stream *s = video_drvdata(file);
	struct cx18 *cx = id->cx;

	strlcpy(vcap->driver, CX18_DRIVER_NAME, sizeof(vcap->driver));
	strlcpy(vcap->card, cx->card_name, sizeof(vcap->card));
	snprintf(vcap->bus_info, sizeof(vcap->bus_info),
		 "PCI:%s", pci_name(cx->pci_dev));
	vcap->capabilities = cx->v4l2_cap;	/* capabilities */
	vcap->device_caps = s->v4l2_dev_caps;	/* device capabilities */
	vcap->capabilities |= V4L2_CAP_DEVICE_CAPS;
	return 0;
}