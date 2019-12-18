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
struct TYPE_2__ {int x; int y; int /*<<< orphan*/  lock; } ;
struct mdp4_crtc {TYPE_1__ cursor; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PENDING_CURSOR ; 
 int /*<<< orphan*/  crtc_flush (struct drm_crtc*) ; 
 int /*<<< orphan*/  request_pending (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int mdp4_crtc_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	unsigned long flags;

	spin_lock_irqsave(&mdp4_crtc->cursor.lock, flags);
	mdp4_crtc->cursor.x = x;
	mdp4_crtc->cursor.y = y;
	spin_unlock_irqrestore(&mdp4_crtc->cursor.lock, flags);

	crtc_flush(crtc);
	request_pending(crtc, PENDING_CURSOR);

	return 0;
}