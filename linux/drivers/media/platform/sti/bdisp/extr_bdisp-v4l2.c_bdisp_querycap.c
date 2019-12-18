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
struct file {int dummy; } ;
struct bdisp_dev {int /*<<< orphan*/  id; TYPE_1__* pdev; } ;
struct bdisp_ctx {struct bdisp_dev* bdisp_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* BDISP_NAME ; 
 struct bdisp_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bdisp_querycap(struct file *file, void *fh,
			  struct v4l2_capability *cap)
{
	struct bdisp_ctx *ctx = fh_to_ctx(fh);
	struct bdisp_dev *bdisp = ctx->bdisp_dev;

	strscpy(cap->driver, bdisp->pdev->name, sizeof(cap->driver));
	strscpy(cap->card, bdisp->pdev->name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s%d",
		 BDISP_NAME, bdisp->id);
	return 0;
}