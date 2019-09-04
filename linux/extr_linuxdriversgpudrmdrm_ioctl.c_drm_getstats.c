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
struct drm_stats {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct drm_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drm_getstats(struct drm_device *dev, void *data,
		 struct drm_file *file_priv)
{
	struct drm_stats *stats = data;

	/* Clear stats to prevent userspace from eating its stack garbage. */
	memset(stats, 0, sizeof(*stats));

	return 0;
}