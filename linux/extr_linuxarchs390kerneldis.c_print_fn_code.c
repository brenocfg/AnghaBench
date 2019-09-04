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
 int insn_length (unsigned char) ; 
 int /*<<< orphan*/  print_insn (char*,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

void print_fn_code(unsigned char *code, unsigned long len)
{
	char buffer[64], *ptr;
	int opsize, i;

	while (len) {
		ptr = buffer;
		opsize = insn_length(*code);
		if (opsize > len)
			break;
		ptr += sprintf(ptr, "%p: ", code);
		for (i = 0; i < opsize; i++)
			ptr += sprintf(ptr, "%02x", code[i]);
		*ptr++ = '\t';
		if (i < 4)
			*ptr++ = '\t';
		ptr += print_insn(ptr, code, (unsigned long) code);
		*ptr++ = '\n';
		*ptr++ = 0;
		printk("%s", buffer);
		code += opsize;
		len -= opsize;
	}
}