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
typedef  char u_char ;
struct spk_synth {int dummy; } ;

/* Variables and functions */
 char PROCSPEECH ; 
 int /*<<< orphan*/  spk_out (char) ; 
 scalar_t__ synth_full () ; 

__attribute__((used)) static const char *synth_immediate(struct spk_synth *synth, const char *buf)
{
	u_char ch;

	while ((ch = (u_char)*buf)) {
		if (synth_full())
			return buf;
		if (ch == '\n')
			ch = PROCSPEECH;
		spk_out(ch);
		buf++;
	}
	return NULL;
}