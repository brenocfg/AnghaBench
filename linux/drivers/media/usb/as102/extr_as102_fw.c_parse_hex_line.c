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

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  atohx (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int parse_hex_line(unsigned char *fw_data, unsigned char *addr,
			  unsigned char *data, int *dataLength,
			  unsigned char *addr_has_changed) {

	int count = 0;
	unsigned char *src, dst;

	if (*fw_data++ != ':') {
		pr_err("invalid firmware file\n");
		return -EFAULT;
	}

	/* locate end of line */
	for (src = fw_data; *src != '\n'; src += 2) {
		atohx(&dst, src);
		/* parse line to split addr / data */
		switch (count) {
		case 0:
			*dataLength = dst;
			break;
		case 1:
			addr[2] = dst;
			break;
		case 2:
			addr[3] = dst;
			break;
		case 3:
			/* check if data is an address */
			if (dst == 0x04)
				*addr_has_changed = 1;
			else
				*addr_has_changed = 0;
			break;
		case  4:
		case  5:
			if (*addr_has_changed)
				addr[(count - 4)] = dst;
			else
				data[(count - 4)] = dst;
			break;
		default:
			data[(count - 4)] = dst;
			break;
		}
		count++;
	}

	/* return read value + ':' + '\n' */
	return (count * 2) + 2;
}