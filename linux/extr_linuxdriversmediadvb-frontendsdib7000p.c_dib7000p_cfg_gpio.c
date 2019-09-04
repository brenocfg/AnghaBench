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
typedef  int u8 ;
struct dib7000p_state {int gpio_dir; int gpio_val; } ;

/* Variables and functions */
 void* dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 

__attribute__((used)) static int dib7000p_cfg_gpio(struct dib7000p_state *st, u8 num, u8 dir, u8 val)
{
	st->gpio_dir = dib7000p_read_word(st, 1029);
	st->gpio_dir &= ~(1 << num);	/* reset the direction bit */
	st->gpio_dir |= (dir & 0x1) << num;	/* set the new direction */
	dib7000p_write_word(st, 1029, st->gpio_dir);

	st->gpio_val = dib7000p_read_word(st, 1030);
	st->gpio_val &= ~(1 << num);	/* reset the direction bit */
	st->gpio_val |= (val & 0x01) << num;	/* set the new value */
	dib7000p_write_word(st, 1030, st->gpio_val);

	return 0;
}