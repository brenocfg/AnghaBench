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
struct osd_layer_config {int dummy; } ;
struct osd_window_state {struct osd_layer_config lconfig; } ;
struct osd_state {int /*<<< orphan*/  lock; struct osd_window_state* win; } ;
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void osd_get_layer_config(struct osd_state *sd, enum osd_layer layer,
				 struct osd_layer_config *lconfig)
{
	struct osd_state *osd = sd;
	struct osd_window_state *win = &osd->win[layer];
	unsigned long flags;

	spin_lock_irqsave(&osd->lock, flags);

	*lconfig = win->lconfig;

	spin_unlock_irqrestore(&osd->lock, flags);
}