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
struct sm501fb_par {int head; int /*<<< orphan*/  pseudo_palette; struct sm501fb_info* info; } ;
struct sm501fb_info {struct fb_info** fb; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct sm501_platdata_fbsub {int dummy; } ;
struct fb_info {int /*<<< orphan*/ * pseudo_palette; struct sm501fb_par* par; } ;
typedef  enum sm501_controller { ____Placeholder_sm501_controller } sm501_controller ;
struct TYPE_2__ {struct sm501_platdata_fbsub* fb_pnl; struct sm501_platdata_fbsub* fb_crt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HEAD_CRT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned char*) ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sm501fb_probe_one(struct sm501fb_info *info,
			     enum sm501_controller head)
{
	unsigned char *name = (head == HEAD_CRT) ? "crt" : "panel";
	struct sm501_platdata_fbsub *pd;
	struct sm501fb_par *par;
	struct fb_info *fbi;

	pd = (head == HEAD_CRT) ? info->pdata->fb_crt : info->pdata->fb_pnl;

	/* Do not initialise if we've not been given any platform data */
	if (pd == NULL) {
		dev_info(info->dev, "no data for fb %s (disabled)\n", name);
		return 0;
	}

	fbi = framebuffer_alloc(sizeof(struct sm501fb_par), info->dev);
	if (!fbi)
		return -ENOMEM;

	par = fbi->par;
	par->info = info;
	par->head = head;
	fbi->pseudo_palette = &par->pseudo_palette;

	info->fb[head] = fbi;

	return 0;
}