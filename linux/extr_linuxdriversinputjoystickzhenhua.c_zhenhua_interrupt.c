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
struct zhenhua {scalar_t__ idx; int /*<<< orphan*/ * data; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ZHENHUA_MAX_LENGTH ; 
 int /*<<< orphan*/  bitrev8 (unsigned char) ; 
 struct zhenhua* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  zhenhua_process_packet (struct zhenhua*) ; 

__attribute__((used)) static irqreturn_t zhenhua_interrupt(struct serio *serio, unsigned char data, unsigned int flags)
{
	struct zhenhua *zhenhua = serio_get_drvdata(serio);

	/* All Zhen Hua packets are 5 bytes. The fact that the first byte
	 * is allways 0xf7 and all others are in range 0x32 - 0xc8 (50-200)
	 * can be used to check and regain sync. */

	if (data == 0xef)
		zhenhua->idx = 0;	/* this byte starts a new packet */
	else if (zhenhua->idx == 0)
		return IRQ_HANDLED;	/* wrong MSB -- ignore this byte */

	if (zhenhua->idx < ZHENHUA_MAX_LENGTH)
		zhenhua->data[zhenhua->idx++] = bitrev8(data);

	if (zhenhua->idx == ZHENHUA_MAX_LENGTH) {
		zhenhua_process_packet(zhenhua);
		zhenhua->idx = 0;
	}

	return IRQ_HANDLED;
}