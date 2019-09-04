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
struct drm_encoder {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct drm_encoder* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct drm_encoder *mdp4_dsi_encoder_init(struct drm_device *dev)
{
	return ERR_PTR(-ENODEV);
}