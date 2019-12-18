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
struct tifm_ms {int cmd_flags; TYPE_1__* req; } ;
struct TYPE_2__ {scalar_t__ need_card_int; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int CARD_INT ; 
 int CMD_READY ; 
 int FIFO_READY ; 

__attribute__((used)) static int tifm_ms_check_status(struct tifm_ms *host)
{
	if (!host->req->error) {
		if (!(host->cmd_flags & CMD_READY))
			return 1;
		if (!(host->cmd_flags & FIFO_READY))
			return 1;
		if (host->req->need_card_int
		    && !(host->cmd_flags & CARD_INT))
			return 1;
	}
	return 0;
}