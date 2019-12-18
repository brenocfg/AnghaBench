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
struct tifm_sd {int cmd_flags; unsigned char* bounce_buf_data; struct tifm_dev* dev; } ;
struct tifm_dev {scalar_t__ addr; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int DATA_CARRY ; 
 scalar_t__ SOCK_MMCSD_DATA ; 
 unsigned char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned char*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void tifm_sd_write_fifo(struct tifm_sd *host, struct page *pg,
			       unsigned int off, unsigned int cnt)
{
	struct tifm_dev *sock = host->dev;
	unsigned char *buf;
	unsigned int pos = 0, val;

	buf = kmap_atomic(pg) + off;
	if (host->cmd_flags & DATA_CARRY) {
		val = host->bounce_buf_data[0] | ((buf[pos++] << 8) & 0xff00);
		writel(val, sock->addr + SOCK_MMCSD_DATA);
		host->cmd_flags &= ~DATA_CARRY;
	}

	while (pos < cnt) {
		val = buf[pos++];
		if (pos == cnt) {
			host->bounce_buf_data[0] = val & 0xff;
			host->cmd_flags |= DATA_CARRY;
			break;
		}
		val |= (buf[pos++] << 8) & 0xff00;
		writel(val, sock->addr + SOCK_MMCSD_DATA);
	}
	kunmap_atomic(buf - off);
}