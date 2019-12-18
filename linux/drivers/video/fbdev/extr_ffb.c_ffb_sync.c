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
struct ffb_par {int dummy; } ;
struct fb_info {scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FFBWait (struct ffb_par*) ; 

__attribute__((used)) static int ffb_sync(struct fb_info *p)
{
	struct ffb_par *par = (struct ffb_par *)p->par;

	FFBWait(par);
	return 0;
}