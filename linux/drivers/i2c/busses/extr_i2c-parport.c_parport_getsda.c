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
struct TYPE_2__ {int /*<<< orphan*/  getsda; } ;

/* Variables and functions */
 TYPE_1__* adapter_parm ; 
 int line_get (struct parport*,int /*<<< orphan*/ *) ; 
 size_t type ; 

__attribute__((used)) static int parport_getsda(void *data)
{
	return line_get((struct parport *) data, &adapter_parm[type].getsda);
}