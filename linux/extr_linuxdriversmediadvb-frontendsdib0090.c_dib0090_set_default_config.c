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
typedef  scalar_t__ u16 ;
struct dib0090_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,scalar_t__,scalar_t__) ; 
 scalar_t__ pgm_read_word (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dib0090_set_default_config(struct dib0090_state *state, const u16 * n)
{
	u16 l, r;

	l = pgm_read_word(n++);
	while (l) {
		r = pgm_read_word(n++);
		do {
			dib0090_write_reg(state, r, pgm_read_word(n++));
			r++;
		} while (--l);
		l = pgm_read_word(n++);
	}
}