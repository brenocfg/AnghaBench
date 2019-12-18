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
typedef  scalar_t__ u32 ;
struct pcmcia_socket {int dummy; } ;
struct pccard_io_map {scalar_t__ start; scalar_t__ stop; } ;
struct db1x_pcmcia_sock {scalar_t__ virt_io; } ;

/* Variables and functions */
 scalar_t__ IO_MAP_SIZE ; 
 struct db1x_pcmcia_sock* to_db1x_socket (struct pcmcia_socket*) ; 

__attribute__((used)) static int au1x00_pcmcia_set_io_map(struct pcmcia_socket *skt,
				    struct pccard_io_map *map)
{
	struct db1x_pcmcia_sock *sock = to_db1x_socket(skt);

	map->start = (u32)sock->virt_io;
	map->stop = map->start + IO_MAP_SIZE;

	return 0;
}