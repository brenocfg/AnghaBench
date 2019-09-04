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
struct gf2k {size_t id; int /*<<< orphan*/  bads; int /*<<< orphan*/  gameport; int /*<<< orphan*/  reads; } ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int GF2K_LENGTH ; 
 struct gf2k* gameport_get_drvdata (struct gameport*) ; 
 scalar_t__* gf2k_length ; 
 int /*<<< orphan*/  gf2k_read (struct gf2k*,unsigned char*) ; 
 scalar_t__ gf2k_read_packet (int /*<<< orphan*/ ,scalar_t__,unsigned char*) ; 

__attribute__((used)) static void gf2k_poll(struct gameport *gameport)
{
	struct gf2k *gf2k = gameport_get_drvdata(gameport);
	unsigned char data[GF2K_LENGTH];

	gf2k->reads++;

	if (gf2k_read_packet(gf2k->gameport, gf2k_length[gf2k->id], data) < gf2k_length[gf2k->id])
		gf2k->bads++;
	else
		gf2k_read(gf2k, data);
}