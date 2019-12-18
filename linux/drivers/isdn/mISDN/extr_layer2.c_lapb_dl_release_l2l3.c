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
struct layer2 {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_LAPB ; 
 int /*<<< orphan*/  PH_DEACTIVATE_REQ ; 
 int /*<<< orphan*/  l2_newid (struct layer2*) ; 
 int /*<<< orphan*/  l2down_create (struct layer2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2up_create (struct layer2*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline void
lapb_dl_release_l2l3(struct layer2 *l2, int f)
{
	if (test_bit(FLG_LAPB, &l2->flag))
		l2down_create(l2, PH_DEACTIVATE_REQ, l2_newid(l2), 0, NULL);
	l2up_create(l2, f, 0, NULL);
}