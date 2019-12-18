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
struct resource {scalar_t__ start; } ;
struct pcmcia_socket {struct bcm63xx_pcmcia_socket* driver_data; } ;
struct pccard_mem_map {int flags; scalar_t__ card_start; scalar_t__ static_start; } ;
struct bcm63xx_pcmcia_socket {struct resource* common_res; struct resource* attr_res; } ;

/* Variables and functions */
 int MAP_ATTRIB ; 

__attribute__((used)) static int bcm63xx_pcmcia_set_mem_map(struct pcmcia_socket *sock,
				      struct pccard_mem_map *map)
{
	struct bcm63xx_pcmcia_socket *skt;
	struct resource *res;

	skt = sock->driver_data;
	if (map->flags & MAP_ATTRIB)
		res = skt->attr_res;
	else
		res = skt->common_res;

	map->static_start = res->start + map->card_start;
	return 0;
}