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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_plane {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int malidp_format_mod_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool malidp_format_mod_supported_per_plane(struct drm_plane *plane,
						  u32 format, u64 modifier)
{
	return malidp_format_mod_supported(plane->dev, format, modifier);
}