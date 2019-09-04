#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  possible_crtcs; } ;
struct nv50_msto {TYPE_1__ encoder; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ENCODER_DPMST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_encoder_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_encoder_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  kfree (struct nv50_msto*) ; 
 struct nv50_msto* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv50_msto ; 
 int /*<<< orphan*/  nv50_msto_help ; 

__attribute__((used)) static int
nv50_msto_new(struct drm_device *dev, u32 heads, const char *name, int id,
	      struct nv50_msto **pmsto)
{
	struct nv50_msto *msto;
	int ret;

	if (!(msto = *pmsto = kzalloc(sizeof(*msto), GFP_KERNEL)))
		return -ENOMEM;

	ret = drm_encoder_init(dev, &msto->encoder, &nv50_msto,
			       DRM_MODE_ENCODER_DPMST, "%s-mst-%d", name, id);
	if (ret) {
		kfree(*pmsto);
		*pmsto = NULL;
		return ret;
	}

	drm_encoder_helper_add(&msto->encoder, &nv50_msto_help);
	msto->encoder.possible_crtcs = heads;
	return 0;
}