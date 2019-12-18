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
struct spk_synth {int /*<<< orphan*/  long_name; TYPE_1__* io_ops; int /*<<< orphan*/  (* synth_immediate ) (struct spk_synth*,char*) ;} ;
struct TYPE_2__ {unsigned char (* synth_in ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  stub1 (struct spk_synth*,char*) ; 
 unsigned char stub2 () ; 

__attribute__((used)) static void synth_interrogate(struct spk_synth *synth)
{
	unsigned char *t, i;
	unsigned char buf[50], rom_v[20];

	synth->synth_immediate(synth, "\x18\x01?");
	for (i = 0; i < 50; i++) {
		buf[i] = synth->io_ops->synth_in();
		if (i > 2 && buf[i] == 0x7f)
			break;
	}
	t = buf + 2;
	for (i = 0; *t != '\r'; t++) {
		rom_v[i] = *t;
		if (++i >= 19)
			break;
	}
	rom_v[i] = 0;
	pr_info("%s: ROM version: %s\n", synth->long_name, rom_v);
}