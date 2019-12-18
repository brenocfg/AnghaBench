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
struct ccwchain {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ccwchain*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccwchain_free(struct ccwchain *chain)
{
	list_del(&chain->next);
	kfree(chain);
}