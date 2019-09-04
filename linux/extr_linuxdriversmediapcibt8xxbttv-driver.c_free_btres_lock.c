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
struct bttv_fh {int resources; } ;
struct bttv {int resources; } ;

/* Variables and functions */
 int VBI_RESOURCES ; 
 int VIDEO_RESOURCES ; 
 int /*<<< orphan*/  disclaim_vbi_lines (struct bttv*) ; 
 int /*<<< orphan*/  disclaim_video_lines (struct bttv*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static
void free_btres_lock(struct bttv *btv, struct bttv_fh *fh, int bits)
{
	if ((fh->resources & bits) != bits) {
		/* trying to free resources not allocated by us ... */
		pr_err("BUG! (btres)\n");
	}
	fh->resources  &= ~bits;
	btv->resources &= ~bits;

	bits = btv->resources;

	if (0 == (bits & VIDEO_RESOURCES))
		disclaim_video_lines(btv);

	if (0 == (bits & VBI_RESOURCES))
		disclaim_vbi_lines(btv);
}