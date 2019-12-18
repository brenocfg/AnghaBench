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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct con3270 {TYPE_1__ view; int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  raw3270_wait_cons_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
con3270_wait_write(struct con3270 *cp)
{
	while (!cp->write) {
		raw3270_wait_cons_dev(cp->view.dev);
		barrier();
	}
}