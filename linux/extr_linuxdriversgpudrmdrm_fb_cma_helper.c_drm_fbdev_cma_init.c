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
struct drm_fb_helper {int /*<<< orphan*/  client; } ;
struct drm_fbdev_cma {struct drm_fb_helper fb_helper; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct drm_fbdev_cma* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_client_add (int /*<<< orphan*/ *) ; 
 int drm_client_init (struct drm_device*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_client_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_cma_helper_funcs ; 
 int drm_fb_helper_fbdev_setup (struct drm_device*,struct drm_fb_helper*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct drm_fbdev_cma*) ; 
 struct drm_fbdev_cma* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_fbdev_cma *drm_fbdev_cma_init(struct drm_device *dev,
	unsigned int preferred_bpp, unsigned int max_conn_count)
{
	struct drm_fbdev_cma *fbdev_cma;
	struct drm_fb_helper *fb_helper;
	int ret;

	fbdev_cma = kzalloc(sizeof(*fbdev_cma), GFP_KERNEL);
	if (!fbdev_cma)
		return ERR_PTR(-ENOMEM);

	fb_helper = &fbdev_cma->fb_helper;

	ret = drm_client_init(dev, &fb_helper->client, "fbdev", NULL);
	if (ret)
		goto err_free;

	ret = drm_fb_helper_fbdev_setup(dev, fb_helper, &drm_fb_cma_helper_funcs,
					preferred_bpp, max_conn_count);
	if (ret)
		goto err_client_put;

	drm_client_add(&fb_helper->client);

	return fbdev_cma;

err_client_put:
	drm_client_release(&fb_helper->client);
err_free:
	kfree(fbdev_cma);

	return ERR_PTR(ret);
}