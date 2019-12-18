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
typedef  char u8 ;

/* Variables and functions */
 int EINVAL ; 
 int get_unaligned_be32 (char*) ; 
 int /*<<< orphan*/  pr_err (char*,char) ; 
 int /*<<< orphan*/  read_bitstream (char*,char*,int*,int) ; 

__attribute__((used)) static int readlength_bitstream(u8 *bitdata, int *lendata, int *offset)
{
	u8 tbuf[4];

	/* read section char */
	read_bitstream(bitdata, tbuf, offset, 1);

	/* make sure it is section 'e' */
	if (tbuf[0] != 'e') {
		pr_err("error: length section is not 'e', but %c\n", tbuf[0]);
		return -EINVAL;
	}

	/* read 4bytes length */
	read_bitstream(bitdata, tbuf, offset, 4);

	*lendata = get_unaligned_be32(tbuf);

	return 0;
}