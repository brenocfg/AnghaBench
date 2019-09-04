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
struct bttv_crop {int /*<<< orphan*/  rect; } ;
struct TYPE_3__ {int /*<<< orphan*/  defrect; } ;
struct TYPE_4__ {TYPE_1__ cropcap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_crop_calc_limits (struct bttv_crop*) ; 
 TYPE_2__* bttv_tvnorms ; 

__attribute__((used)) static void
bttv_crop_reset(struct bttv_crop *c, unsigned int norm)
{
	c->rect = bttv_tvnorms[norm].cropcap.defrect;
	bttv_crop_calc_limits(c);
}