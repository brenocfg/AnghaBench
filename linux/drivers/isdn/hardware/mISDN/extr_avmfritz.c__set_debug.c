#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* debug; } ;
struct TYPE_5__ {TYPE_1__ dch; } ;
struct fritzcard {TYPE_3__* bch; TYPE_2__ isac; } ;
struct TYPE_6__ {void* debug; } ;

/* Variables and functions */
 void* debug ; 

__attribute__((used)) static void
_set_debug(struct fritzcard *card)
{
	card->isac.dch.debug = debug;
	card->bch[0].debug = debug;
	card->bch[1].debug = debug;
}