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
struct omap_vout_device {scalar_t__ mirror; scalar_t__ rotation; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_rotation_enabled(const struct omap_vout_device *vout)
{
	return vout->rotation || vout->mirror;
}