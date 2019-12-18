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
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ qeth_set_access_ctrl_online (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l2_start_ipassists(struct qeth_card *card)
{
	/* configure isolation level */
	if (qeth_set_access_ctrl_online(card, 0))
		return -ENODEV;
	return 0;
}