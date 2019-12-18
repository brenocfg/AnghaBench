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
struct rvt_wss {struct rvt_wss* entries; } ;
struct rvt_dev_info {struct rvt_wss* wss; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rvt_wss*) ; 

void rvt_wss_exit(struct rvt_dev_info *rdi)
{
	struct rvt_wss *wss = rdi->wss;

	if (!wss)
		return;

	/* coded to handle partially initialized and repeat callers */
	kfree(wss->entries);
	wss->entries = NULL;
	kfree(rdi->wss);
	rdi->wss = NULL;
}