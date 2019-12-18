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
struct tty_struct {scalar_t__ disc_data; } ;
struct serport {int /*<<< orphan*/  lock; int /*<<< orphan*/  serio; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int SERIO_FRAME ; 
 unsigned int SERIO_PARITY ; 
 int /*<<< orphan*/  SERPORT_ACTIVE ; 
#define  TTY_FRAME 129 
#define  TTY_PARITY 128 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned char const,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serport_ldisc_receive(struct tty_struct *tty, const unsigned char *cp, char *fp, int count)
{
	struct serport *serport = (struct serport*) tty->disc_data;
	unsigned long flags;
	unsigned int ch_flags = 0;
	int i;

	spin_lock_irqsave(&serport->lock, flags);

	if (!test_bit(SERPORT_ACTIVE, &serport->flags))
		goto out;

	for (i = 0; i < count; i++) {
		if (fp) {
			switch (fp[i]) {
			case TTY_FRAME:
				ch_flags = SERIO_FRAME;
				break;

			case TTY_PARITY:
				ch_flags = SERIO_PARITY;
				break;

			default:
				ch_flags = 0;
				break;
			}
		}

		serio_interrupt(serport->serio, cp[i], ch_flags);
	}

out:
	spin_unlock_irqrestore(&serport->lock, flags);
}