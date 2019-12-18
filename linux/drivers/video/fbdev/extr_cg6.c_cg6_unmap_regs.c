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
struct platform_device {int /*<<< orphan*/ * resource; } ;
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ screen_base; } ;
struct cg6_thc {int dummy; } ;
struct cg6_tec {int dummy; } ;
struct cg6_par {scalar_t__ fhc; scalar_t__ bt; scalar_t__ thc; scalar_t__ tec; scalar_t__ fbc; } ;
struct bt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void cg6_unmap_regs(struct platform_device *op, struct fb_info *info,
			   struct cg6_par *par)
{
	if (par->fbc)
		of_iounmap(&op->resource[0], par->fbc, 4096);
	if (par->tec)
		of_iounmap(&op->resource[0], par->tec, sizeof(struct cg6_tec));
	if (par->thc)
		of_iounmap(&op->resource[0], par->thc, sizeof(struct cg6_thc));
	if (par->bt)
		of_iounmap(&op->resource[0], par->bt, sizeof(struct bt_regs));
	if (par->fhc)
		of_iounmap(&op->resource[0], par->fhc, sizeof(u32));

	if (info->screen_base)
		of_iounmap(&op->resource[0], info->screen_base,
			   info->fix.smem_len);
}