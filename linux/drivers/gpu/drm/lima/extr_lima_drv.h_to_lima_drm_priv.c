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
struct lima_drm_priv {int dummy; } ;
struct drm_file {struct lima_drm_priv* driver_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline struct lima_drm_priv *
to_lima_drm_priv(struct drm_file *file)
{
	return file->driver_priv;
}