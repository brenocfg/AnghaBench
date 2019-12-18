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
struct sti_tvout {int debugfs_registered; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 struct sti_tvout* to_sti_tvout (struct drm_encoder*) ; 
 int tvout_debugfs_init (struct sti_tvout*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sti_tvout_late_register(struct drm_encoder *encoder)
{
	struct sti_tvout *tvout = to_sti_tvout(encoder);
	int ret;

	if (tvout->debugfs_registered)
		return 0;

	ret = tvout_debugfs_init(tvout, encoder->dev->primary);
	if (ret)
		return ret;

	tvout->debugfs_registered = true;
	return 0;
}