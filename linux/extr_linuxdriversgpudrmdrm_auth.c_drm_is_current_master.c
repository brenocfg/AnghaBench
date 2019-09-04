#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_file {TYPE_2__* minor; int /*<<< orphan*/  master; scalar_t__ is_master; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ master; } ;

/* Variables and functions */
 scalar_t__ drm_lease_owner (int /*<<< orphan*/ ) ; 

bool drm_is_current_master(struct drm_file *fpriv)
{
	return fpriv->is_master && drm_lease_owner(fpriv->master) == fpriv->minor->dev->master;
}