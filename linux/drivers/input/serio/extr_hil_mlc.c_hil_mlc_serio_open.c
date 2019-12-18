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
struct serio {struct hil_mlc_serio_map* port_data; } ;
struct hil_mlc_serio_map {struct hil_mlc* mlc; } ;
struct hil_mlc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/ * serio_get_drvdata (struct serio*) ; 

__attribute__((used)) static int hil_mlc_serio_open(struct serio *serio)
{
	struct hil_mlc_serio_map *map;
	struct hil_mlc *mlc;

	if (serio_get_drvdata(serio) != NULL)
		return -EBUSY;

	map = serio->port_data;
	BUG_ON(map == NULL);

	mlc = map->mlc;
	BUG_ON(mlc == NULL);

	return 0;
}