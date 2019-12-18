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
struct tmdc {unsigned char exists; unsigned char bads; int /*<<< orphan*/ * port; int /*<<< orphan*/  gameport; int /*<<< orphan*/  reads; } ;
struct gameport {int dummy; } ;

/* Variables and functions */
 int TMDC_MAX_LENGTH ; 
 struct tmdc* gameport_get_drvdata (struct gameport*) ; 
 scalar_t__ tmdc_parse_packet (int /*<<< orphan*/ ,unsigned char*) ; 
 unsigned char tmdc_read_packet (int /*<<< orphan*/ ,unsigned char**) ; 

__attribute__((used)) static void tmdc_poll(struct gameport *gameport)
{
	unsigned char data[2][TMDC_MAX_LENGTH];
	struct tmdc *tmdc = gameport_get_drvdata(gameport);
	unsigned char r, bad = 0;
	int i;

	tmdc->reads++;

	if ((r = tmdc_read_packet(tmdc->gameport, data)) != tmdc->exists)
		bad = 1;
	else {
		for (i = 0; i < 2; i++) {
			if (r & (1 << i) & tmdc->exists) {

				if (tmdc_parse_packet(tmdc->port[i], data[i]))
					bad = 1;
			}
		}
	}

	tmdc->bads += bad;
}