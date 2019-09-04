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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* int_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_1__* to_target (struct config_item*) ; 

__attribute__((used)) static ssize_t pcie_gadget_int_type_show(struct config_item *item, char *buf)
{
	return sprintf(buf, "%s", to_target(item)->int_type);
}