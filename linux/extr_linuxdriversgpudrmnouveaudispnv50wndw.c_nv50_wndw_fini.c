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
struct nv50_wndw {int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_notify_put (int /*<<< orphan*/ *) ; 

void
nv50_wndw_fini(struct nv50_wndw *wndw)
{
	nvif_notify_put(&wndw->notify);
}