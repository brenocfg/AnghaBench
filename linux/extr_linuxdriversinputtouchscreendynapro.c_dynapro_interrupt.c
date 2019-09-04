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
struct dynapro {unsigned char* data; size_t idx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DYNAPRO_RESPONSE_BEGIN_BYTE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dynapro_process_data (struct dynapro*) ; 
 struct dynapro* serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static irqreturn_t dynapro_interrupt(struct serio *serio,
		unsigned char data, unsigned int flags)
{
	struct dynapro *pdynapro = serio_get_drvdata(serio);

	pdynapro->data[pdynapro->idx] = data;

	if (DYNAPRO_RESPONSE_BEGIN_BYTE & pdynapro->data[0])
		dynapro_process_data(pdynapro);
	else
		dev_dbg(&serio->dev, "unknown/unsynchronized data: %x\n",
			pdynapro->data[0]);

	return IRQ_HANDLED;
}