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
struct bbc_i2c_client {int dummy; } ;

/* Variables and functions */
 int bbc_i2c_writeb (struct bbc_i2c_client*,char,int) ; 

int bbc_i2c_write_buf(struct bbc_i2c_client *client,
		      char *buf, int len, int off)
{
	int ret = 0;

	while (len > 0) {
		ret = bbc_i2c_writeb(client, *buf, off);
		if (ret < 0)
			break;
		len--;
		buf++;
		off++;
	}
	return ret;
}