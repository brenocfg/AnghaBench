#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct hva_dev {TYPE_1__* pdev; TYPE_2__* vdev; } ;
struct hva_ctx {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HVA_NAME ; 
 struct hva_dev* ctx_to_hdev (struct hva_ctx*) ; 
 struct hva_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hva_querycap(struct file *file, void *priv,
			struct v4l2_capability *cap)
{
	struct hva_ctx *ctx = fh_to_ctx(file->private_data);
	struct hva_dev *hva = ctx_to_hdev(ctx);

	strscpy(cap->driver, HVA_NAME, sizeof(cap->driver));
	strscpy(cap->card, hva->vdev->name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s",
		 hva->pdev->name);

	return 0;
}