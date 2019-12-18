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
typedef  enum media_request_state { ____Placeholder_media_request_state } media_request_state ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ NR_OF_MEDIA_REQUEST_STATE ; 
 scalar_t__ WARN_ON (int) ; 
 char const** request_state ; 

__attribute__((used)) static const char *
media_request_state_str(enum media_request_state state)
{
	BUILD_BUG_ON(ARRAY_SIZE(request_state) != NR_OF_MEDIA_REQUEST_STATE);

	if (WARN_ON(state >= ARRAY_SIZE(request_state)))
		return "invalid";
	return request_state[state];
}