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
struct TYPE_3__ {scalar_t__ hostnotification; scalar_t__ reflect_promisc; scalar_t__ role; } ;
struct TYPE_4__ {TYPE_1__ sbp; } ;
struct qeth_card {TYPE_2__ options; } ;

/* Variables and functions */

__attribute__((used)) static bool qeth_bridgeport_is_in_use(struct qeth_card *card)
{
	return (card->options.sbp.role || card->options.sbp.reflect_promisc ||
		card->options.sbp.hostnotification);
}