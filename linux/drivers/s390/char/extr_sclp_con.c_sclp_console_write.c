#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct console {int dummy; } ;
struct TYPE_3__ {void* next; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_del (struct list_head*) ; 
 scalar_t__ list_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ sclp_chars_in_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_con_columns ; 
 int /*<<< orphan*/  sclp_con_lock ; 
 TYPE_1__ sclp_con_pages ; 
 scalar_t__ sclp_con_suspended ; 
 int /*<<< orphan*/  sclp_con_timer ; 
 int /*<<< orphan*/  sclp_con_width_htab ; 
 int /*<<< orphan*/ * sclp_conbuf ; 
 int /*<<< orphan*/  sclp_conbuf_emit () ; 
 scalar_t__ sclp_console_drop_buffer () ; 
 int /*<<< orphan*/  sclp_console_full ; 
 int /*<<< orphan*/ * sclp_make_buffer (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sclp_sync_wait () ; 
 int sclp_write (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sclp_console_write(struct console *console, const char *message,
		   unsigned int count)
{
	unsigned long flags;
	void *page;
	int written;

	if (count == 0)
		return;
	spin_lock_irqsave(&sclp_con_lock, flags);
	/*
	 * process escape characters, write message into buffer,
	 * send buffer to SCLP
	 */
	do {
		/* make sure we have a console output buffer */
		if (sclp_conbuf == NULL) {
			if (list_empty(&sclp_con_pages))
				sclp_console_full++;
			while (list_empty(&sclp_con_pages)) {
				if (sclp_con_suspended)
					goto out;
				if (sclp_console_drop_buffer())
					break;
				spin_unlock_irqrestore(&sclp_con_lock, flags);
				sclp_sync_wait();
				spin_lock_irqsave(&sclp_con_lock, flags);
			}
			page = sclp_con_pages.next;
			list_del((struct list_head *) page);
			sclp_conbuf = sclp_make_buffer(page, sclp_con_columns,
						       sclp_con_width_htab);
		}
		/* try to write the string to the current output buffer */
		written = sclp_write(sclp_conbuf, (const unsigned char *)
				     message, count);
		if (written == count)
			break;
		/*
		 * Not all characters could be written to the current
		 * output buffer. Emit the buffer, create a new buffer
		 * and then output the rest of the string.
		 */
		spin_unlock_irqrestore(&sclp_con_lock, flags);
		sclp_conbuf_emit();
		spin_lock_irqsave(&sclp_con_lock, flags);
		message += written;
		count -= written;
	} while (count > 0);
	/* Setup timer to output current console buffer after 1/10 second */
	if (sclp_conbuf != NULL && sclp_chars_in_buffer(sclp_conbuf) != 0 &&
	    !timer_pending(&sclp_con_timer)) {
		mod_timer(&sclp_con_timer, jiffies + HZ / 10);
	}
out:
	spin_unlock_irqrestore(&sclp_con_lock, flags);
}