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
typedef  unsigned int u64 ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMEPORT_MODE_RAW ; 
 int /*<<< orphan*/  gameport_close (struct gameport*) ; 
 scalar_t__ gameport_open (struct gameport*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gameport_read (struct gameport*) ; 
 unsigned int ktime_get_ns () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

__attribute__((used)) static int gameport_measure_speed(struct gameport *gameport)
{
	unsigned int i, t, tx;
	u64 t1, t2, t3;
	unsigned long flags;

	if (gameport_open(gameport, NULL, GAMEPORT_MODE_RAW))
		return 0;

	tx = ~0;

	for (i = 0; i < 50; i++) {
		local_irq_save(flags);
		t1 = ktime_get_ns();
		for (t = 0; t < 50; t++)
			gameport_read(gameport);
		t2 = ktime_get_ns();
		t3 = ktime_get_ns();
		local_irq_restore(flags);
		udelay(i * 10);
		t = (t2 - t1) - (t3 - t2);
		if (t < tx)
			tx = t;
	}

	gameport_close(gameport);
	t = 1000000 * 50;
	if (tx)
		t /= tx;
	return t;
}