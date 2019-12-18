#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int currindex; int highindex; int lowindex; int /*<<< orphan*/  command; } ;
struct TYPE_4__ {TYPE_1__ indexing; scalar_t__ alive; } ;

/* Variables and functions */
 int /*<<< orphan*/  index_count ; 
 TYPE_2__* synth ; 
 int /*<<< orphan*/  synth_printf (int /*<<< orphan*/ ,int,int) ; 

void synth_insert_next_index(int sent_num)
{
	int out;

	if (synth->alive) {
		if (sent_num == 0) {
			synth->indexing.currindex++;
			index_count++;
			if (synth->indexing.currindex >
					synth->indexing.highindex)
				synth->indexing.currindex =
					synth->indexing.lowindex;
		}

		out = synth->indexing.currindex * 10 + sent_num;
		synth_printf(synth->indexing.command, out, out);
	}
}