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
struct fsl_mc_obj_desc {scalar_t__ id; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ id; int /*<<< orphan*/  type; } ;
struct fsl_mc_device {TYPE_1__ obj_desc; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fsl_mc_device_match(struct fsl_mc_device *mc_dev,
				struct fsl_mc_obj_desc *obj_desc)
{
	return mc_dev->obj_desc.id == obj_desc->id &&
	       strcmp(mc_dev->obj_desc.type, obj_desc->type) == 0;

}