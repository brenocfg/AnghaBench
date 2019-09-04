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
struct inbuf_t {int inputstate; int* data; size_t head; size_t tail; struct cardstate* cs; } ;
struct cardstate {scalar_t__ mstate; int /*<<< orphan*/  dev; scalar_t__ dle; } ;

/* Variables and functions */
#define  DLE_FLAG 128 
 int INS_DLE_char ; 
 int INS_DLE_command ; 
 int INS_command ; 
 scalar_t__ MS_LOCKED ; 
 size_t RBUFSIZE ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void handle_dle(struct inbuf_t *inbuf)
{
	struct cardstate *cs = inbuf->cs;

	if (cs->mstate == MS_LOCKED)
		return;		/* no DLE processing in lock mode */

	if (!(inbuf->inputstate & INS_DLE_char)) {
		/* no DLE pending */
		if (inbuf->data[inbuf->head] == DLE_FLAG &&
		    (cs->dle || inbuf->inputstate & INS_DLE_command)) {
			/* start of DLE sequence */
			inbuf->head++;
			if (inbuf->head == inbuf->tail ||
			    inbuf->head == RBUFSIZE) {
				/* end of buffer, save for later processing */
				inbuf->inputstate |= INS_DLE_char;
				return;
			}
		} else {
			/* regular data byte */
			return;
		}
	}

	/* consume pending DLE */
	inbuf->inputstate &= ~INS_DLE_char;

	switch (inbuf->data[inbuf->head]) {
	case 'X':	/* begin of event message */
		if (inbuf->inputstate & INS_command)
			dev_notice(cs->dev,
				   "received <DLE>X in command mode\n");
		inbuf->inputstate |= INS_command | INS_DLE_command;
		inbuf->head++;	/* byte consumed */
		break;
	case '.':	/* end of event message */
		if (!(inbuf->inputstate & INS_DLE_command))
			dev_notice(cs->dev,
				   "received <DLE>. without <DLE>X\n");
		inbuf->inputstate &= ~INS_DLE_command;
		/* return to data mode if in DLE mode */
		if (cs->dle)
			inbuf->inputstate &= ~INS_command;
		inbuf->head++;	/* byte consumed */
		break;
	case DLE_FLAG:	/* DLE in data stream */
		/* mark as quoted */
		inbuf->inputstate |= INS_DLE_char;
		if (!(cs->dle || inbuf->inputstate & INS_DLE_command))
			dev_notice(cs->dev,
				   "received <DLE><DLE> not in DLE mode\n");
		break;	/* quoted byte left in buffer */
	default:
		dev_notice(cs->dev, "received <DLE><%02x>\n",
			   inbuf->data[inbuf->head]);
		/* quoted byte left in buffer */
	}
}