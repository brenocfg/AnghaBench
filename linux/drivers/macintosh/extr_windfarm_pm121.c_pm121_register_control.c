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
struct wf_control {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct wf_control** controls ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ wf_get_control (struct wf_control*) ; 

__attribute__((used)) static struct wf_control* pm121_register_control(struct wf_control *ct,
						 const char *match,
						 unsigned int id)
{
	if (controls[id] == NULL && !strcmp(ct->name, match)) {
		if (wf_get_control(ct) == 0)
			controls[id] = ct;
	}
	return controls[id];
}