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
typedef  int /*<<< orphan*/  u16 ;
struct octeon_device {int /*<<< orphan*/  eswitch_mode; } ;
struct lio_devlink_priv {struct octeon_device* oct; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct lio_devlink_priv* devlink_priv (struct devlink*) ; 

__attribute__((used)) static int
liquidio_eswitch_mode_get(struct devlink *devlink, u16 *mode)
{
	struct lio_devlink_priv *priv;
	struct octeon_device *oct;

	priv = devlink_priv(devlink);
	oct = priv->oct;

	*mode = oct->eswitch_mode;

	return 0;
}