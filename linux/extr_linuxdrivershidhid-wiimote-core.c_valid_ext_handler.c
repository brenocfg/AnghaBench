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
struct wiimod_ops {int flags; int /*<<< orphan*/  in_ext; } ;

/* Variables and functions */
 int WIIMOD_FLAG_EXT16 ; 
 int WIIMOD_FLAG_EXT8 ; 

__attribute__((used)) static bool valid_ext_handler(const struct wiimod_ops *ops, size_t len)
{
	if (!ops->in_ext)
		return false;
	if ((ops->flags & WIIMOD_FLAG_EXT8) && len < 8)
		return false;
	if ((ops->flags & WIIMOD_FLAG_EXT16) && len < 16)
		return false;

	return true;
}