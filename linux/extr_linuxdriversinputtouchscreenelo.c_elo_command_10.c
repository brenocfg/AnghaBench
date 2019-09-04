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
struct elo {scalar_t__ expected_packet; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  response; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  serio; } ;

/* Variables and functions */
 int ELO10_LEAD_BYTE ; 
 int ELO10_PACKET_LEN ; 
 scalar_t__ ELO10_TOUCH_PACKET ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_continue_rx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_pause_rx (int /*<<< orphan*/ ) ; 
 scalar_t__ serio_write (int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ toupper (unsigned char) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elo_command_10(struct elo *elo, unsigned char *packet)
{
	int rc = -1;
	int i;
	unsigned char csum = 0xaa + ELO10_LEAD_BYTE;

	mutex_lock(&elo->cmd_mutex);

	serio_pause_rx(elo->serio);
	elo->expected_packet = toupper(packet[0]);
	init_completion(&elo->cmd_done);
	serio_continue_rx(elo->serio);

	if (serio_write(elo->serio, ELO10_LEAD_BYTE))
		goto out;

	for (i = 0; i < ELO10_PACKET_LEN; i++) {
		csum += packet[i];
		if (serio_write(elo->serio, packet[i]))
			goto out;
	}

	if (serio_write(elo->serio, csum))
		goto out;

	wait_for_completion_timeout(&elo->cmd_done, HZ);

	if (elo->expected_packet == ELO10_TOUCH_PACKET) {
		/* We are back in reporting mode, the command was ACKed */
		memcpy(packet, elo->response, ELO10_PACKET_LEN);
		rc = 0;
	}

 out:
	mutex_unlock(&elo->cmd_mutex);
	return rc;
}