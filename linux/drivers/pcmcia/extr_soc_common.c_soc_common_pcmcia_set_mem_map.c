#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct soc_pcmcia_socket {unsigned short* spd_attr; unsigned short* spd_mem; TYPE_1__* ops; struct resource res_mem; struct resource res_attr; } ;
struct pcmcia_socket {int dummy; } ;
struct pccard_mem_map {unsigned short speed; size_t map; int flags; scalar_t__ card_start; scalar_t__ static_start; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_timing ) (struct soc_pcmcia_socket*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int MAP_0WS ; 
 int MAP_16BIT ; 
 int MAP_ACTIVE ; 
 int MAP_ATTRIB ; 
 int MAP_AUTOSZ ; 
 int MAP_USE_WAIT ; 
 int MAP_WRPROT ; 
 size_t MAX_WIN ; 
 int /*<<< orphan*/  debug (struct soc_pcmcia_socket*,int,char*,...) ; 
 int /*<<< orphan*/  stub1 (struct soc_pcmcia_socket*) ; 
 struct soc_pcmcia_socket* to_soc_pcmcia_socket (struct pcmcia_socket*) ; 

__attribute__((used)) static int soc_common_pcmcia_set_mem_map(
	struct pcmcia_socket *sock, struct pccard_mem_map *map)
{
	struct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);
	struct resource *res;
	unsigned short speed = map->speed;

	debug(skt, 2, "map %u speed %u card_start %08x\n",
		map->map, map->speed, map->card_start);
	debug(skt, 2, "flags: %s%s%s%s%s%s%s%s\n",
		(map->flags == 0)		? "<NONE>"	: "",
		(map->flags & MAP_ACTIVE)	? "ACTIVE "	: "",
		(map->flags & MAP_16BIT)	? "16BIT "	: "",
		(map->flags & MAP_AUTOSZ)	? "AUTOSZ "	: "",
		(map->flags & MAP_0WS)		? "0WS "	: "",
		(map->flags & MAP_WRPROT)	? "WRPROT "	: "",
		(map->flags & MAP_ATTRIB)	? "ATTRIB "	: "",
		(map->flags & MAP_USE_WAIT)	? "USE_WAIT "	: "");

	if (map->map >= MAX_WIN)
		return -EINVAL;

	if (map->flags & MAP_ACTIVE) {
		if (speed == 0)
			speed = 300;
	} else {
		speed = 0;
	}

	if (map->flags & MAP_ATTRIB) {
		res = &skt->res_attr;
		skt->spd_attr[map->map] = speed;
		skt->spd_mem[map->map] = 0;
	} else {
		res = &skt->res_mem;
		skt->spd_attr[map->map] = 0;
		skt->spd_mem[map->map] = speed;
	}

	skt->ops->set_timing(skt);

	map->static_start = res->start + map->card_start;

	return 0;
}