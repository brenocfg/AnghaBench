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
#define  BUSPHASE_COMMAND 134 
#define  BUSPHASE_DATA_IN 133 
#define  BUSPHASE_DATA_OUT 132 
#define  BUSPHASE_MESSAGE_IN 131 
#define  BUSPHASE_MESSAGE_OUT 130 
#define  BUSPHASE_SELECT 129 
#define  BUSPHASE_STATUS 128 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void show_busphase(unsigned char stat)
{
	switch(stat) {
	case BUSPHASE_COMMAND:
		printk( "BUSPHASE_COMMAND\n");
		break;
	case BUSPHASE_MESSAGE_IN:
		printk( "BUSPHASE_MESSAGE_IN\n");
		break;
	case BUSPHASE_MESSAGE_OUT:
		printk( "BUSPHASE_MESSAGE_OUT\n");
		break;
	case BUSPHASE_DATA_IN:
		printk( "BUSPHASE_DATA_IN\n");
		break;
	case BUSPHASE_DATA_OUT:
		printk( "BUSPHASE_DATA_OUT\n");
		break;
	case BUSPHASE_STATUS:
		printk( "BUSPHASE_STATUS\n");
		break;
	case BUSPHASE_SELECT:
		printk( "BUSPHASE_SELECT\n");
		break;
	default:
		printk( "BUSPHASE_other: 0x%x\n", stat);
		break;
	}
}