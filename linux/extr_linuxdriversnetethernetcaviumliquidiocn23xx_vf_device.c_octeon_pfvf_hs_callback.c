#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  params; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct octeon_mbox_cmd {int recv_len; scalar_t__ data; TYPE_2__ msg; } ;
struct octeon_device {int /*<<< orphan*/  pfvf_hsword; } ;
struct lio_version {int major; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  CN23XX_MAILBOX_MSGPARAM_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_pfvf_hs_callback(struct octeon_device *oct,
				    struct octeon_mbox_cmd *cmd,
				    void *arg)
{
	u32 major = 0;

	memcpy((uint8_t *)&oct->pfvf_hsword, cmd->msg.s.params,
	       CN23XX_MAILBOX_MSGPARAM_SIZE);
	if (cmd->recv_len > 1)  {
		major = ((struct lio_version *)(cmd->data))->major;
		major = major << 16;
	}

	atomic_set((atomic_t *)arg, major | 1);
}