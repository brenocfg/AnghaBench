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
struct nfp_app {int dummy; } ;
typedef  enum devlink_eswitch_mode { ____Placeholder_devlink_eswitch_mode } devlink_eswitch_mode ;

/* Variables and functions */
 int DEVLINK_ESWITCH_MODE_SWITCHDEV ; 

__attribute__((used)) static enum devlink_eswitch_mode eswitch_mode_get(struct nfp_app *app)
{
	return DEVLINK_ESWITCH_MODE_SWITCHDEV;
}