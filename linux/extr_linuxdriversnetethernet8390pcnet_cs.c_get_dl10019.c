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
typedef  int u_char ;
struct pcmcia_device {struct net_device* priv; } ;
struct net_device {scalar_t__ base_addr; scalar_t__* dev_addr; } ;
struct hw_info {int dummy; } ;

/* Variables and functions */
 struct hw_info dl10019_info ; 
 struct hw_info dl10022_info ; 
 int inb (scalar_t__) ; 
 scalar_t__ inb_p (scalar_t__) ; 

__attribute__((used)) static struct hw_info *get_dl10019(struct pcmcia_device *link)
{
    struct net_device *dev = link->priv;
    int i;
    u_char sum;

    for (sum = 0, i = 0x14; i < 0x1c; i++)
	sum += inb_p(dev->base_addr + i);
    if (sum != 0xff)
	return NULL;
    for (i = 0; i < 6; i++)
	dev->dev_addr[i] = inb_p(dev->base_addr + 0x14 + i);
    i = inb(dev->base_addr + 0x1f);
    return ((i == 0x91)||(i == 0x99)) ? &dl10022_info : &dl10019_info;
}