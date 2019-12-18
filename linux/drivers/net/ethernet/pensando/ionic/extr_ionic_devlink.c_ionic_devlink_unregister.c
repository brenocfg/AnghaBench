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
struct ionic {int /*<<< orphan*/  dl_port; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_port_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 struct devlink* priv_to_devlink (struct ionic*) ; 

void ionic_devlink_unregister(struct ionic *ionic)
{
	struct devlink *dl = priv_to_devlink(ionic);

	devlink_port_unregister(&ionic->dl_port);
	devlink_unregister(dl);
}