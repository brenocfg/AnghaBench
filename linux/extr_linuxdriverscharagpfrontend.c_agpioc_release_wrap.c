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
struct agp_file_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  agp_controller_release_current (int /*<<< orphan*/ ,struct agp_file_private*) ; 
 TYPE_1__ agp_fe ; 

int agpioc_release_wrap(struct agp_file_private *priv)
{
	DBG("");
	agp_controller_release_current(agp_fe.current_controller, priv);
	return 0;
}