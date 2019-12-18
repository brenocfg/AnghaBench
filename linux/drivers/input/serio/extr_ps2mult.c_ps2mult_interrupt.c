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
struct ps2mult_port {int /*<<< orphan*/  serio; scalar_t__ registered; } ;
struct ps2mult {int escape; int /*<<< orphan*/  lock; struct ps2mult_port* in_port; struct ps2mult_port* ports; struct ps2mult_port* out_port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  PS2MULT_BSYNC 133 
#define  PS2MULT_ESCAPE 132 
 size_t PS2MULT_KBD_PORT ; 
#define  PS2MULT_KB_SELECTOR 131 
 size_t PS2MULT_MOUSE_PORT ; 
#define  PS2MULT_MS_SELECTOR 130 
#define  PS2MULT_SESSION_END 129 
#define  PS2MULT_SESSION_START 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct ps2mult* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ps2mult_interrupt(struct serio *serio,
				     unsigned char data, unsigned int dfl)
{
	struct ps2mult *psm = serio_get_drvdata(serio);
	struct ps2mult_port *in_port;
	unsigned long flags;

	dev_dbg(&serio->dev, "Received %02x flags %02x\n", data, dfl);

	spin_lock_irqsave(&psm->lock, flags);

	if (psm->escape) {
		psm->escape = false;
		in_port = psm->in_port;
		if (in_port->registered)
			serio_interrupt(in_port->serio, data, dfl);
		goto out;
	}

	switch (data) {
	case PS2MULT_ESCAPE:
		dev_dbg(&serio->dev, "ESCAPE\n");
		psm->escape = true;
		break;

	case PS2MULT_BSYNC:
		dev_dbg(&serio->dev, "BSYNC\n");
		psm->in_port = psm->out_port;
		break;

	case PS2MULT_SESSION_START:
		dev_dbg(&serio->dev, "SS\n");
		break;

	case PS2MULT_SESSION_END:
		dev_dbg(&serio->dev, "SE\n");
		break;

	case PS2MULT_KB_SELECTOR:
		dev_dbg(&serio->dev, "KB\n");
		psm->in_port = &psm->ports[PS2MULT_KBD_PORT];
		break;

	case PS2MULT_MS_SELECTOR:
		dev_dbg(&serio->dev, "MS\n");
		psm->in_port = &psm->ports[PS2MULT_MOUSE_PORT];
		break;

	default:
		in_port = psm->in_port;
		if (in_port->registered)
			serio_interrupt(in_port->serio, data, dfl);
		break;
	}

 out:
	spin_unlock_irqrestore(&psm->lock, flags);
	return IRQ_HANDLED;
}