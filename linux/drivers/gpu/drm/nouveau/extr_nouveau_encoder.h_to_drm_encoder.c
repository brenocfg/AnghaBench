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
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {struct drm_encoder base; } ;
struct nouveau_encoder {TYPE_1__ base; } ;

/* Variables and functions */

__attribute__((used)) static inline struct drm_encoder *to_drm_encoder(struct nouveau_encoder *enc)
{
	return &enc->base.base;
}