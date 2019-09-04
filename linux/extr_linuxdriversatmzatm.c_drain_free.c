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
struct atm_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pool; } ;

/* Variables and functions */
 TYPE_1__* ZATM_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drain_free(struct atm_dev *dev,int pool)
{
	skb_queue_purge(&ZATM_DEV(dev)->pool[pool]);
}