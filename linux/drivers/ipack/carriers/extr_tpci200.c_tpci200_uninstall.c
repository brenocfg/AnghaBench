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
struct tpci200_board {int /*<<< orphan*/  slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpci200_unregister (struct tpci200_board*) ; 

__attribute__((used)) static void tpci200_uninstall(struct tpci200_board *tpci200)
{
	tpci200_unregister(tpci200);
	kfree(tpci200->slots);
}