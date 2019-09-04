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
struct serio {int /*<<< orphan*/  dev; } ;
struct egalax {unsigned char* data; int idx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EGALAX_FORMAT_PRESSURE_BIT ; 
 int EGALAX_FORMAT_START_BIT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  egalax_process_data (struct egalax*) ; 
 scalar_t__ likely (int) ; 
 struct egalax* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t egalax_interrupt(struct serio *serio,
				    unsigned char data, unsigned int flags)
{
	struct egalax *egalax = serio_get_drvdata(serio);
	int pkt_len;

	egalax->data[egalax->idx++] = data;

	if (likely(egalax->data[0] & EGALAX_FORMAT_START_BIT)) {
		pkt_len = egalax->data[0] & EGALAX_FORMAT_PRESSURE_BIT ? 6 : 5;
		if (pkt_len == egalax->idx) {
			egalax_process_data(egalax);
			egalax->idx = 0;
		}
	} else {
		dev_dbg(&serio->dev, "unknown/unsynchronized data: %x\n",
			egalax->data[0]);
		egalax->idx = 0;
	}

	return IRQ_HANDLED;
}