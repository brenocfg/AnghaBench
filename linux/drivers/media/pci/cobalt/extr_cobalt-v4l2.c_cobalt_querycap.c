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
struct file {int dummy; } ;
struct cobalt_stream {struct cobalt* cobalt; } ;
struct cobalt {scalar_t__ have_hsma_tx; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct cobalt_stream* video_drvdata (struct file*) ; 

__attribute__((used)) static int cobalt_querycap(struct file *file, void *priv_fh,
				struct v4l2_capability *vcap)
{
	struct cobalt_stream *s = video_drvdata(file);
	struct cobalt *cobalt = s->cobalt;

	strscpy(vcap->driver, "cobalt", sizeof(vcap->driver));
	strscpy(vcap->card, "cobalt", sizeof(vcap->card));
	snprintf(vcap->bus_info, sizeof(vcap->bus_info),
		 "PCIe:%s", pci_name(cobalt->pci_dev));
	vcap->capabilities = V4L2_CAP_STREAMING | V4L2_CAP_READWRITE |
		V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_DEVICE_CAPS;
	if (cobalt->have_hsma_tx)
		vcap->capabilities |= V4L2_CAP_VIDEO_OUTPUT;
	return 0;
}