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
struct TYPE_2__ {int max_level; } ;
struct asd_sas_port {TYPE_1__ disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int sas_ex_level_discovery (struct asd_sas_port*,int) ; 

__attribute__((used)) static int sas_ex_bfs_disc(struct asd_sas_port *port)
{
	int res;
	int level;

	do {
		level = port->disc.max_level;
		res = sas_ex_level_discovery(port, level);
		mb();
	} while (level < port->disc.max_level);

	return res;
}