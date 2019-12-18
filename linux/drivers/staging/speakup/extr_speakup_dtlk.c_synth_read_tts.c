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
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  port_tts; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ speakup_info ; 
 scalar_t__ synth_readable () ; 
 int synth_status ; 

__attribute__((used)) static char synth_read_tts(void)
{
	u_char ch;

	while (!synth_readable())
		cpu_relax();
	ch = synth_status & 0x7f;
	outb_p(ch, speakup_info.port_tts);
	while (synth_readable())
		cpu_relax();
	return (char)ch;
}