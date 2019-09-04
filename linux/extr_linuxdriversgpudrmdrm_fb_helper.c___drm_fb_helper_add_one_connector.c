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
struct drm_fb_helper_connector {struct drm_connector* connector; } ;
struct drm_fb_helper {int connector_count; unsigned int connector_info_alloc_count; struct drm_fb_helper_connector** connector_info; int /*<<< orphan*/  lock; } ;
struct drm_connector {int dummy; } ;
typedef  int /*<<< orphan*/  fb_conn ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_connector_get (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_fbdev_emulation ; 
 struct drm_fb_helper_connector** krealloc (struct drm_fb_helper_connector**,size_t,int /*<<< orphan*/ ) ; 
 struct drm_fb_helper_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __drm_fb_helper_add_one_connector(struct drm_fb_helper *fb_helper,
					     struct drm_connector *connector)
{
	struct drm_fb_helper_connector *fb_conn;
	struct drm_fb_helper_connector **temp;
	unsigned int count;

	if (!drm_fbdev_emulation)
		return 0;

	lockdep_assert_held(&fb_helper->lock);

	count = fb_helper->connector_count + 1;

	if (count > fb_helper->connector_info_alloc_count) {
		size_t size = count * sizeof(fb_conn);

		temp = krealloc(fb_helper->connector_info, size, GFP_KERNEL);
		if (!temp)
			return -ENOMEM;

		fb_helper->connector_info_alloc_count = count;
		fb_helper->connector_info = temp;
	}

	fb_conn = kzalloc(sizeof(*fb_conn), GFP_KERNEL);
	if (!fb_conn)
		return -ENOMEM;

	drm_connector_get(connector);
	fb_conn->connector = connector;
	fb_helper->connector_info[fb_helper->connector_count++] = fb_conn;

	return 0;
}