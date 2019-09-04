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
struct sti_tvout {int debugfs_registered; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 struct sti_tvout* to_sti_tvout (struct drm_encoder*) ; 

__attribute__((used)) static void sti_tvout_early_unregister(struct drm_encoder *encoder)
{
	struct sti_tvout *tvout = to_sti_tvout(encoder);

	if (!tvout->debugfs_registered)
		return;

	tvout->debugfs_registered = false;
}