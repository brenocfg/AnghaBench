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
typedef  int u32 ;
struct de_private {scalar_t__ media_type; int /*<<< orphan*/  media_timer; int /*<<< orphan*/  dev; scalar_t__ media_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DE_MEDIA_AUI ; 
 scalar_t__ DE_MEDIA_BNC ; 
 scalar_t__ DE_MEDIA_TP_AUTO ; 
 scalar_t__ DE_TIMER_LINK ; 
 scalar_t__ DE_TIMER_NO_LINK ; 
 int LinkFail ; 
 int LinkPass ; 
 int /*<<< orphan*/  de_link_down (struct de_private*) ; 
 int /*<<< orphan*/  de_link_up (struct de_private*) ; 
 int /*<<< orphan*/  de_ok_to_advertise (struct de_private*,scalar_t__) ; 
 int /*<<< orphan*/  de_set_media (struct de_private*) ; 
 int /*<<< orphan*/  de_start_rxtx (struct de_private*) ; 
 int /*<<< orphan*/  de_stop_rxtx (struct de_private*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void de_media_interrupt (struct de_private *de, u32 status)
{
	if (status & LinkPass) {
		/* Ignore if current media is AUI or BNC and we can't use TP */
		if ((de->media_type == DE_MEDIA_AUI ||
		     de->media_type == DE_MEDIA_BNC) &&
		    (de->media_lock ||
		     !de_ok_to_advertise(de, DE_MEDIA_TP_AUTO)))
			return;
		/* If current media is not TP, change it to TP */
		if ((de->media_type == DE_MEDIA_AUI ||
		     de->media_type == DE_MEDIA_BNC)) {
			de->media_type = DE_MEDIA_TP_AUTO;
			de_stop_rxtx(de);
			de_set_media(de);
			de_start_rxtx(de);
		}
		de_link_up(de);
		mod_timer(&de->media_timer, jiffies + DE_TIMER_LINK);
		return;
	}

	BUG_ON(!(status & LinkFail));
	/* Mark the link as down only if current media is TP */
	if (netif_carrier_ok(de->dev) && de->media_type != DE_MEDIA_AUI &&
	    de->media_type != DE_MEDIA_BNC) {
		de_link_down(de);
		mod_timer(&de->media_timer, jiffies + DE_TIMER_NO_LINK);
	}
}