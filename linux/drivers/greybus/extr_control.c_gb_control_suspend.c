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
struct gb_control {int /*<<< orphan*/  connection; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 

int gb_control_suspend(struct gb_control *control)
{
	gb_connection_disable(control->connection);

	return 0;
}