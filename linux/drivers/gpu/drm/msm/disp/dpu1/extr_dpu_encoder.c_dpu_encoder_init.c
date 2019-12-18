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
struct drm_device {int /*<<< orphan*/  dev; } ;
struct dpu_encoder_virt {int enabled; struct drm_encoder base; int /*<<< orphan*/  enc_spinlock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_encoder* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct dpu_encoder_virt*) ; 
 struct dpu_encoder_virt* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_funcs ; 
 int /*<<< orphan*/  dpu_encoder_helper_funcs ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct drm_encoder *dpu_encoder_init(struct drm_device *dev,
		int drm_enc_mode)
{
	struct dpu_encoder_virt *dpu_enc = NULL;
	int rc = 0;

	dpu_enc = devm_kzalloc(dev->dev, sizeof(*dpu_enc), GFP_KERNEL);
	if (!dpu_enc)
		return ERR_PTR(ENOMEM);

	rc = drm_encoder_init(dev, &dpu_enc->base, &dpu_encoder_funcs,
			drm_enc_mode, NULL);
	if (rc) {
		devm_kfree(dev->dev, dpu_enc);
		return ERR_PTR(rc);
	}

	drm_encoder_helper_add(&dpu_enc->base, &dpu_encoder_helper_funcs);

	spin_lock_init(&dpu_enc->enc_spinlock);
	dpu_enc->enabled = false;

	return &dpu_enc->base;
}