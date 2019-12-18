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
struct spk_synth {int /*<<< orphan*/  clear; TYPE_1__* io_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* synth_out ) (struct spk_synth*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* flush_buffer ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (struct spk_synth*,int /*<<< orphan*/ ) ; 

void spk_synth_flush(struct spk_synth *synth)
{
	synth->io_ops->flush_buffer();
	synth->io_ops->synth_out(synth, synth->clear);
}