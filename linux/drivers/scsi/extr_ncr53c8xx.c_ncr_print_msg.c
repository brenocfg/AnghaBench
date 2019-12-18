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
typedef  int /*<<< orphan*/  u_char ;
struct ccb {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ADDR (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spi_print_msg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ncr_print_msg(struct ccb *cp, char *label, u_char *msg)
{
	PRINT_ADDR(cp->cmd, "%s: ", label);

	spi_print_msg(msg);
	printk("\n");
}