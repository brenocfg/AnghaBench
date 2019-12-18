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
struct r3964_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  R3964_BREAK ; 
 int /*<<< orphan*/  R3964_FRAME ; 
 int /*<<< orphan*/  R3964_OVERRUN ; 
 int /*<<< orphan*/  R3964_PARITY ; 
 int /*<<< orphan*/  R3964_UNKNOWN ; 
 int /*<<< orphan*/  TRACE_PE (char*,...) ; 
#define  TTY_BREAK 132 
#define  TTY_FRAME 131 
#define  TTY_NORMAL 130 
#define  TTY_OVERRUN 129 
#define  TTY_PARITY 128 

__attribute__((used)) static void receive_error(struct r3964_info *pInfo, const char flag)
{
	switch (flag) {
	case TTY_NORMAL:
		break;
	case TTY_BREAK:
		TRACE_PE("received break");
		pInfo->flags |= R3964_BREAK;
		break;
	case TTY_PARITY:
		TRACE_PE("parity error");
		pInfo->flags |= R3964_PARITY;
		break;
	case TTY_FRAME:
		TRACE_PE("frame error");
		pInfo->flags |= R3964_FRAME;
		break;
	case TTY_OVERRUN:
		TRACE_PE("frame overrun");
		pInfo->flags |= R3964_OVERRUN;
		break;
	default:
		TRACE_PE("receive_error - unknown flag %d", flag);
		pInfo->flags |= R3964_UNKNOWN;
		break;
	}
}