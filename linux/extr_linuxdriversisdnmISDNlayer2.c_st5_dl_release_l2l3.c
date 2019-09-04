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
 int DL_RELEASE_CNF ; 
 int DL_RELEASE_IND ; 
 int /*<<< orphan*/  FLG_PEND_REL ; 
 int /*<<< orphan*/  l2up_create (struct layer2*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

inline void
st5_dl_release_l2l3(struct layer2 *l2)
{
	int pr;

	if (test_and_clear_bit(FLG_PEND_REL, &l2->flag))
		pr = DL_RELEASE_CNF;
	else
		pr = DL_RELEASE_IND;
	l2up_create(l2, pr, 0, NULL);
}