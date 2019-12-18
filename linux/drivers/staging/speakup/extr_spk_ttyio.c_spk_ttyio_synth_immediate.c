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
typedef  char u_char ;
struct spk_synth {char procspeech; TYPE_1__* io_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* synth_out ) (struct spk_synth*,char) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  speakup_tty ; 
 int /*<<< orphan*/  stub1 (struct spk_synth*,char) ; 
 int tty_write_room (int /*<<< orphan*/ ) ; 

const char *spk_ttyio_synth_immediate(struct spk_synth *synth, const char *buff)
{
	u_char ch;

	while ((ch = *buff)) {
		if (ch == '\n')
			ch = synth->procspeech;
		if (tty_write_room(speakup_tty) < 1 ||
		    !synth->io_ops->synth_out(synth, ch))
			return buff;
		buff++;
	}
	return NULL;
}