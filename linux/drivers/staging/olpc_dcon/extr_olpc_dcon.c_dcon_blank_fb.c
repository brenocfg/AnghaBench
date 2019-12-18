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
struct dcon_priv {int ignore_fb_events; TYPE_1__* client; int /*<<< orphan*/  fbinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int fb_blank (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_fb_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_fb_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dcon_blank_fb(struct dcon_priv *dcon, bool blank)
{
	int err;

	console_lock();
	lock_fb_info(dcon->fbinfo);

	dcon->ignore_fb_events = true;
	err = fb_blank(dcon->fbinfo,
		       blank ? FB_BLANK_POWERDOWN : FB_BLANK_UNBLANK);
	dcon->ignore_fb_events = false;
	unlock_fb_info(dcon->fbinfo);
	console_unlock();

	if (err) {
		dev_err(&dcon->client->dev, "couldn't %sblank framebuffer\n",
			blank ? "" : "un");
		return false;
	}
	return true;
}