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
struct ionic {int dummy; } ;
struct devlink {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct devlink* devlink_alloc (int /*<<< orphan*/ *,int) ; 
 struct ionic* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  ionic_dl_ops ; 

struct ionic *ionic_devlink_alloc(struct device *dev)
{
	struct devlink *dl;

	dl = devlink_alloc(&ionic_dl_ops, sizeof(struct ionic));

	return devlink_priv(dl);
}