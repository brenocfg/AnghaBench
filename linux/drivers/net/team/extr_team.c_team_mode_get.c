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
struct team_mode_item {struct team_mode* mode; } ;
struct team_mode {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 struct team_mode_item* __find_mode (char const*) ; 
 int /*<<< orphan*/  mode_list_lock ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct team_mode *team_mode_get(const char *kind)
{
	struct team_mode_item *mitem;
	const struct team_mode *mode = NULL;

	spin_lock(&mode_list_lock);
	mitem = __find_mode(kind);
	if (!mitem) {
		spin_unlock(&mode_list_lock);
		request_module("team-mode-%s", kind);
		spin_lock(&mode_list_lock);
		mitem = __find_mode(kind);
	}
	if (mitem) {
		mode = mitem->mode;
		if (!try_module_get(mode->owner))
			mode = NULL;
	}

	spin_unlock(&mode_list_lock);
	return mode;
}