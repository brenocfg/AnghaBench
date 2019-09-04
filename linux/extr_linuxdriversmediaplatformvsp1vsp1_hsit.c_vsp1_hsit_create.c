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
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct vsp1_hsit {int inverse; TYPE_1__ entity; } ;
struct vsp1_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_hsit* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_PIXEL_ENC_CONV ; 
 int /*<<< orphan*/  VSP1_ENTITY_HSI ; 
 int /*<<< orphan*/  VSP1_ENTITY_HST ; 
 struct vsp1_hsit* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsit_entity_ops ; 
 int /*<<< orphan*/  hsit_ops ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct vsp1_hsit *vsp1_hsit_create(struct vsp1_device *vsp1, bool inverse)
{
	struct vsp1_hsit *hsit;
	int ret;

	hsit = devm_kzalloc(vsp1->dev, sizeof(*hsit), GFP_KERNEL);
	if (hsit == NULL)
		return ERR_PTR(-ENOMEM);

	hsit->inverse = inverse;

	hsit->entity.ops = &hsit_entity_ops;

	if (inverse)
		hsit->entity.type = VSP1_ENTITY_HSI;
	else
		hsit->entity.type = VSP1_ENTITY_HST;

	ret = vsp1_entity_init(vsp1, &hsit->entity, inverse ? "hsi" : "hst",
			       2, &hsit_ops,
			       MEDIA_ENT_F_PROC_VIDEO_PIXEL_ENC_CONV);
	if (ret < 0)
		return ERR_PTR(ret);

	return hsit;
}