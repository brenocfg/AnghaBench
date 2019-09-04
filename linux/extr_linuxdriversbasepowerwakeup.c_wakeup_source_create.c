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
struct wakeup_source {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct wakeup_source* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_source_prepare (struct wakeup_source*,int /*<<< orphan*/ *) ; 

struct wakeup_source *wakeup_source_create(const char *name)
{
	struct wakeup_source *ws;

	ws = kmalloc(sizeof(*ws), GFP_KERNEL);
	if (!ws)
		return NULL;

	wakeup_source_prepare(ws, name ? kstrdup_const(name, GFP_KERNEL) : NULL);
	return ws;
}