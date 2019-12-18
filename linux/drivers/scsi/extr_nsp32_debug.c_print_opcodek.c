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
#define  NOTEXT_GROUP 130 
#define  RESERVED_GROUP 129 
#define  VENDOR_GROUP 128 
 char*** commands ; 
 size_t group (unsigned char) ; 
 int /*<<< orphan*/  printk (char*,char const*,unsigned char) ; 
 char const* reserved ; 
 char const* unknown ; 
 char const* vendor ; 

__attribute__((used)) static void print_opcodek(unsigned char opcode)
{
	const char **table = commands[ group(opcode) ];

	switch ((unsigned long) table) {
	case RESERVED_GROUP:
		printk("%s[%02x] ", reserved, opcode); 
		break;
	case NOTEXT_GROUP:
		printk("%s(notext)[%02x] ", unknown, opcode); 
		break;
	case VENDOR_GROUP:
		printk("%s[%02x] ", vendor, opcode); 
		break;
	default:
		if (table[opcode & 0x1f] != unknown)
			printk("%s[%02x] ", table[opcode & 0x1f], opcode);
		else
			printk("%s[%02x] ", unknown, opcode);
		break;
	}
}