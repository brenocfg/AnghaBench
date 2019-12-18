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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct tw5864_input {int nr; TYPE_1__* root; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct tw5864_input* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw5864_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	struct tw5864_input *input = video_drvdata(file);

	strscpy(cap->driver, "tw5864", sizeof(cap->driver));
	snprintf(cap->card, sizeof(cap->card), "TW5864 Encoder %d",
		 input->nr);
	sprintf(cap->bus_info, "PCI:%s", pci_name(input->root->pci));
	return 0;
}