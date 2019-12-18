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
struct venus_core {int /*<<< orphan*/  max_sessions_supported; } ;
struct hfi_max_sessions_supported {int /*<<< orphan*/  max_sessions; } ;

/* Variables and functions */

__attribute__((used)) static void parse_max_sessions(struct venus_core *core, const void *data)
{
	const struct hfi_max_sessions_supported *sessions = data;

	core->max_sessions_supported = sessions->max_sessions;
}