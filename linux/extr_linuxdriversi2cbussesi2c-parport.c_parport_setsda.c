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
struct parport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  setsda; } ;

/* Variables and functions */
 TYPE_1__* adapter_parm ; 
 int /*<<< orphan*/  line_set (struct parport*,int,int /*<<< orphan*/ *) ; 
 size_t type ; 

__attribute__((used)) static void parport_setsda(void *data, int state)
{
	line_set((struct parport *) data, state, &adapter_parm[type].setsda);
}