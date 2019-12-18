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
typedef  int /*<<< orphan*/  u_char ;
struct sym_tcb {TYPE_1__* starget; } ;
struct sym_hcb {struct sym_tcb* target; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  spi_print_msg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sym_print_nego_msg(struct sym_hcb *np, int target, char *label, u_char *msg)
{
	struct sym_tcb *tp = &np->target[target];
	dev_info(&tp->starget->dev, "%s: ", label);

	spi_print_msg(msg);
	printf("\n");
}