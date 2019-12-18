#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct raw3215_req {int /*<<< orphan*/  len; int /*<<< orphan*/  type; int /*<<< orphan*/  residual; struct raw3215_info* info; } ;
struct raw3215_info {char* inbuf; int /*<<< orphan*/  flags; int /*<<< orphan*/  written; int /*<<< orphan*/  count; int /*<<< orphan*/  empty_wait; int /*<<< orphan*/ * queued_read; int /*<<< orphan*/ * queued_write; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int cstat; int dstat; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CTRLCHAR_CTRL 130 
 unsigned int CTRLCHAR_MASK ; 
#define  CTRLCHAR_NONE 129 
#define  CTRLCHAR_SYSRQ 128 
 int /*<<< orphan*/  EBCASC (char*,int) ; 
 int /*<<< orphan*/  RAW3215_FREE ; 
 int /*<<< orphan*/  RAW3215_READ ; 
 int /*<<< orphan*/  RAW3215_WORKING ; 
 int /*<<< orphan*/  RAW3215_WRITE ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 unsigned int ctrlchar_handle (char*,int,struct tty_struct*) ; 
 struct raw3215_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3215_free_req (struct raw3215_req*) ; 
 int /*<<< orphan*/  raw3215_mk_read_req (struct raw3215_info*) ; 
 int /*<<< orphan*/  raw3215_next_io (struct raw3215_info*,struct tty_struct*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raw3215_irq(struct ccw_device *cdev, unsigned long intparm,
			struct irb *irb)
{
	struct raw3215_info *raw;
	struct raw3215_req *req;
	struct tty_struct *tty;
	int cstat, dstat;
	int count;

	raw = dev_get_drvdata(&cdev->dev);
	req = (struct raw3215_req *) intparm;
	tty = tty_port_tty_get(&raw->port);
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;
	if (cstat != 0)
		raw3215_next_io(raw, tty);
	if (dstat & 0x01) { /* we got a unit exception */
		dstat &= ~0x01;	 /* we can ignore it */
	}
	switch (dstat) {
	case 0x80:
		if (cstat != 0)
			break;
		/* Attention interrupt, someone hit the enter key */
		raw3215_mk_read_req(raw);
		raw3215_next_io(raw, tty);
		break;
	case 0x08:
	case 0x0C:
		/* Channel end interrupt. */
		if ((raw = req->info) == NULL)
			goto put_tty;	     /* That shouldn't happen ... */
		if (req->type == RAW3215_READ) {
			/* store residual count, then wait for device end */
			req->residual = irb->scsw.cmd.count;
		}
		if (dstat == 0x08)
			break;
		/* else, fall through */
	case 0x04:
		/* Device end interrupt. */
		if ((raw = req->info) == NULL)
			goto put_tty;	     /* That shouldn't happen ... */
		if (req->type == RAW3215_READ && tty != NULL) {
			unsigned int cchar;

			count = 160 - req->residual;
			EBCASC(raw->inbuf, count);
			cchar = ctrlchar_handle(raw->inbuf, count, tty);
			switch (cchar & CTRLCHAR_MASK) {
			case CTRLCHAR_SYSRQ:
				break;

			case CTRLCHAR_CTRL:
				tty_insert_flip_char(&raw->port, cchar,
						TTY_NORMAL);
				tty_flip_buffer_push(&raw->port);
				break;

			case CTRLCHAR_NONE:
				if (count < 2 ||
				    (strncmp(raw->inbuf+count-2, "\252n", 2) &&
				     strncmp(raw->inbuf+count-2, "^n", 2)) ) {
					/* add the auto \n */
					raw->inbuf[count] = '\n';
					count++;
				} else
					count -= 2;
				tty_insert_flip_string(&raw->port, raw->inbuf,
						count);
				tty_flip_buffer_push(&raw->port);
				break;
			}
		} else if (req->type == RAW3215_WRITE) {
			raw->count -= req->len;
			raw->written -= req->len;
		}
		raw->flags &= ~RAW3215_WORKING;
		raw3215_free_req(req);
		/* check for empty wait */
		if (waitqueue_active(&raw->empty_wait) &&
		    raw->queued_write == NULL &&
		    raw->queued_read == NULL) {
			wake_up_interruptible(&raw->empty_wait);
		}
		raw3215_next_io(raw, tty);
		break;
	default:
		/* Strange interrupt, I'll do my best to clean up */
		if (req != NULL && req->type != RAW3215_FREE) {
			if (req->type == RAW3215_WRITE) {
				raw->count -= req->len;
				raw->written -= req->len;
			}
			raw->flags &= ~RAW3215_WORKING;
			raw3215_free_req(req);
		}
		raw3215_next_io(raw, tty);
	}
put_tty:
	tty_kref_put(tty);
}