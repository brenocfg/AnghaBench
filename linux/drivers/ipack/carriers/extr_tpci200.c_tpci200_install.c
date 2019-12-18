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
struct tpci200_slot {int dummy; } ;
struct tpci200_board {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * slots; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TPCI200_NB_SLOT ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int tpci200_register (struct tpci200_board*) ; 

__attribute__((used)) static int tpci200_install(struct tpci200_board *tpci200)
{
	int res;

	tpci200->slots = kcalloc(TPCI200_NB_SLOT, sizeof(struct tpci200_slot),
				 GFP_KERNEL);
	if (tpci200->slots == NULL)
		return -ENOMEM;

	res = tpci200_register(tpci200);
	if (res) {
		kfree(tpci200->slots);
		tpci200->slots = NULL;
		return res;
	}

	mutex_init(&tpci200->mutex);
	return 0;
}