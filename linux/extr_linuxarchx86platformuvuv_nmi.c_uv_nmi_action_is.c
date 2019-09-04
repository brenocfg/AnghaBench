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

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_nmi_action ; 

__attribute__((used)) static inline bool uv_nmi_action_is(const char *action)
{
	return (strncmp(uv_nmi_action, action, strlen(action)) == 0);
}