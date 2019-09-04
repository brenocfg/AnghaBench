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
typedef  int u8 ;
struct rave_sp {int /*<<< orphan*/  event_notifier_list; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rave_sp_action_pack (unsigned char const,unsigned char const) ; 
 int rave_sp_reply_code (unsigned char const) ; 
 int /*<<< orphan*/  rave_sp_write (struct rave_sp*,int*,int) ; 

__attribute__((used)) static void rave_sp_receive_event(struct rave_sp *sp,
				  const unsigned char *data, size_t length)
{
	u8 cmd[] = {
		[0] = rave_sp_reply_code(data[0]),
		[1] = data[1],
	};

	rave_sp_write(sp, cmd, sizeof(cmd));

	blocking_notifier_call_chain(&sp->event_notifier_list,
				     rave_sp_action_pack(data[0], data[2]),
				     NULL);
}