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
struct basic_ring {scalar_t__ lastWrite; scalar_t__ ringBase; } ;
struct typhoon {int /*<<< orphan*/  command_lock; scalar_t__ ioaddr; struct basic_ring cmdRing; } ;
struct cmd_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_COMMAND_NO_RESPONSE (struct cmd_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPHOON_CMD_HELLO_RESP ; 
 scalar_t__ TYPHOON_REG_CMD_READY ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  typhoon_inc_cmd_index (scalar_t__*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
typhoon_hello(struct typhoon *tp)
{
	struct basic_ring *ring = &tp->cmdRing;
	struct cmd_desc *cmd;

	/* We only get a hello request if we've not sent anything to the
	 * card in a long while. If the lock is held, then we're in the
	 * process of issuing a command, so we don't need to respond.
	 */
	if(spin_trylock(&tp->command_lock)) {
		cmd = (struct cmd_desc *)(ring->ringBase + ring->lastWrite);
		typhoon_inc_cmd_index(&ring->lastWrite, 1);

		INIT_COMMAND_NO_RESPONSE(cmd, TYPHOON_CMD_HELLO_RESP);
		wmb();
		iowrite32(ring->lastWrite, tp->ioaddr + TYPHOON_REG_CMD_READY);
		spin_unlock(&tp->command_lock);
	}
}