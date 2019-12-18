#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* data; int len; scalar_t__ user; } ;
typedef  TYPE_1__ capiloaddatapart ;
struct TYPE_6__ {unsigned int port; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int EFAULT ; 
 int FWBUF_SIZE ; 
 unsigned char SEND_CONFIG ; 
 int /*<<< orphan*/  b1_put_byte (unsigned int,unsigned char) ; 
 int /*<<< orphan*/  b1_put_word (unsigned int,int) ; 
 scalar_t__ copy_from_user (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

int b1_load_config(avmcard *card, capiloaddatapart *config)
{
	unsigned char buf[FWBUF_SIZE];
	unsigned char *dp;
	unsigned int base = card->port;
	int i, j, left;

	dp = config->data;
	left = config->len;
	if (left) {
		b1_put_byte(base, SEND_CONFIG);
		b1_put_word(base, 1);
		b1_put_byte(base, SEND_CONFIG);
		b1_put_word(base, left);
	}
	while (left > FWBUF_SIZE) {
		if (config->user) {
			if (copy_from_user(buf, dp, FWBUF_SIZE))
				return -EFAULT;
		} else {
			memcpy(buf, dp, FWBUF_SIZE);
		}
		for (i = 0; i < FWBUF_SIZE; ) {
			b1_put_byte(base, SEND_CONFIG);
			for (j = 0; j < 4; j++) {
				b1_put_byte(base, buf[i++]);
			}
		}
		left -= FWBUF_SIZE;
		dp += FWBUF_SIZE;
	}
	if (left) {
		if (config->user) {
			if (copy_from_user(buf, dp, left))
				return -EFAULT;
		} else {
			memcpy(buf, dp, left);
		}
		for (i = 0; i < left; ) {
			b1_put_byte(base, SEND_CONFIG);
			for (j = 0; j < 4; j++) {
				if (i < left)
					b1_put_byte(base, buf[i++]);
				else
					b1_put_byte(base, 0);
			}
		}
	}
	return 0;
}