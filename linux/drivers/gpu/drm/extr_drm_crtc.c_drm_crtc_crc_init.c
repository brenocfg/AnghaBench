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
struct TYPE_2__ {int /*<<< orphan*/  source; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; } ;
struct drm_crtc {TYPE_1__ crc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_crtc_crc_init(struct drm_crtc *crtc)
{
#ifdef CONFIG_DEBUG_FS
	spin_lock_init(&crtc->crc.lock);
	init_waitqueue_head(&crtc->crc.wq);
	crtc->crc.source = kstrdup("auto", GFP_KERNEL);
	if (!crtc->crc.source)
		return -ENOMEM;
#endif
	return 0;
}