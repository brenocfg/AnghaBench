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
typedef  int u8 ;
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int pcmcia_read_config_byte (struct pcmcia_device*,int,int*) ; 
 int pcmcia_write_config_byte (struct pcmcia_device*,int,int) ; 

__attribute__((used)) static int quirk_post_ibm(struct pcmcia_device *link)
{
	u8 val;
	int ret;

	ret = pcmcia_read_config_byte(link, 0x800, &val);
	if (ret)
		goto failed;

	ret = pcmcia_write_config_byte(link, 0x800, val | 1);
	if (ret)
		goto failed;
	return 0;

 failed:
	return -ENODEV;
}