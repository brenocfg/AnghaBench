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
struct vmballoon {unsigned long capabilities; int /*<<< orphan*/  max_page_size; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VMW_BALLOON_2M_PAGE ; 
 int /*<<< orphan*/  VMW_BALLOON_4K_PAGE ; 
 unsigned long VMW_BALLOON_BASIC_CMDS ; 
 int VMW_BALLOON_BATCHED_2M_CMDS ; 
 int VMW_BALLOON_BATCHED_CMDS ; 
 int /*<<< orphan*/  VMW_BALLOON_CMD_START ; 
#define  VMW_BALLOON_SUCCESS 129 
#define  VMW_BALLOON_SUCCESS_WITH_CAPABILITIES 128 
 unsigned long __vmballoon_cmd (struct vmballoon*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int vmballoon_send_start(struct vmballoon *b, unsigned long req_caps)
{
	unsigned long status, capabilities;

	status = __vmballoon_cmd(b, VMW_BALLOON_CMD_START, req_caps, 0,
				 &capabilities);

	switch (status) {
	case VMW_BALLOON_SUCCESS_WITH_CAPABILITIES:
		b->capabilities = capabilities;
		break;
	case VMW_BALLOON_SUCCESS:
		b->capabilities = VMW_BALLOON_BASIC_CMDS;
		break;
	default:
		return -EIO;
	}

	/*
	 * 2MB pages are only supported with batching. If batching is for some
	 * reason disabled, do not use 2MB pages, since otherwise the legacy
	 * mechanism is used with 2MB pages, causing a failure.
	 */
	b->max_page_size = VMW_BALLOON_4K_PAGE;
	if ((b->capabilities & VMW_BALLOON_BATCHED_2M_CMDS) &&
	    (b->capabilities & VMW_BALLOON_BATCHED_CMDS))
		b->max_page_size = VMW_BALLOON_2M_PAGE;


	return 0;
}