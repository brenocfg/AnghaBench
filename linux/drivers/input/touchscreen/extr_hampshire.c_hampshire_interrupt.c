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
struct hampshire {unsigned char* data; size_t idx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HAMPSHIRE_RESPONSE_BEGIN_BYTE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hampshire_process_data (struct hampshire*) ; 
 struct hampshire* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t hampshire_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct hampshire *phampshire = serio_get_drvdata(serio);

	phampshire->data[phampshire->idx] = data;

	if (HAMPSHIRE_RESPONSE_BEGIN_BYTE & phampshire->data[0])
		hampshire_process_data(phampshire);
	else
		dev_dbg(&serio->dev, "unknown/unsynchronized data: %x\n",
			phampshire->data[0]);

	return IRQ_HANDLED;
}