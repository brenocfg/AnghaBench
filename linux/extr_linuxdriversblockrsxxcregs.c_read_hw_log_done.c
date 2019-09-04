#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* buf; size_t buf_len; } ;
struct rsxx_cardinfo {TYPE_1__ log; } ;
struct creg_cmd {char* buf; int cnt8; int status; } ;

/* Variables and functions */
 int CREG_STAT_LOG_PENDING ; 
 size_t LOG_BUF_SIZE8 ; 
 int /*<<< orphan*/  hw_log_msg (struct rsxx_cardinfo*,char*,int) ; 
 int min (int,size_t) ; 
 int /*<<< orphan*/  rsxx_read_hw_log (struct rsxx_cardinfo*) ; 
 int substrncpy (char*,char*,int) ; 

__attribute__((used)) static void read_hw_log_done(struct rsxx_cardinfo *card,
			     struct creg_cmd *cmd,
			     int st)
{
	char *buf;
	char *log_str;
	int cnt;
	int len;
	int off;

	buf = cmd->buf;
	off = 0;

	/* Failed getting the log message */
	if (st)
		return;

	while (off < cmd->cnt8) {
		log_str = &card->log.buf[card->log.buf_len];
		cnt = min(cmd->cnt8 - off, LOG_BUF_SIZE8 - card->log.buf_len);
		len = substrncpy(log_str, &buf[off], cnt);

		off += len;
		card->log.buf_len += len;

		/*
		 * Flush the log if we've hit the end of a message or if we've
		 * run out of buffer space.
		 */
		if ((log_str[len - 1] == '\0')  ||
		    (card->log.buf_len == LOG_BUF_SIZE8)) {
			if (card->log.buf_len != 1) /* Don't log blank lines. */
				hw_log_msg(card, card->log.buf,
					   card->log.buf_len);
			card->log.buf_len = 0;
		}

	}

	if (cmd->status & CREG_STAT_LOG_PENDING)
		rsxx_read_hw_log(card);
}