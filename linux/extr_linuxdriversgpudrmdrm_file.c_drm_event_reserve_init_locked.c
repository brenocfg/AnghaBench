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
struct drm_pending_event {struct drm_file* file_priv; int /*<<< orphan*/  pending_link; struct drm_event* event; } ;
struct drm_file {scalar_t__ event_space; int /*<<< orphan*/  pending_event_list; } ;
struct drm_event {scalar_t__ length; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_event_reserve_init_locked(struct drm_device *dev,
				  struct drm_file *file_priv,
				  struct drm_pending_event *p,
				  struct drm_event *e)
{
	if (file_priv->event_space < e->length)
		return -ENOMEM;

	file_priv->event_space -= e->length;

	p->event = e;
	list_add(&p->pending_link, &file_priv->pending_event_list);
	p->file_priv = file_priv;

	return 0;
}