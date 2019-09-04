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
typedef  int u8 ;
struct TYPE_2__ {int gpio_dir; int gpio_val; } ;
struct dib8000_state {TYPE_1__ cfg; } ;

/* Variables and functions */
 void* dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 

__attribute__((used)) static int dib8000_cfg_gpio(struct dib8000_state *st, u8 num, u8 dir, u8 val)
{
	st->cfg.gpio_dir = dib8000_read_word(st, 1029);
	st->cfg.gpio_dir &= ~(1 << num);	/* reset the direction bit */
	st->cfg.gpio_dir |= (dir & 0x1) << num;	/* set the new direction */
	dib8000_write_word(st, 1029, st->cfg.gpio_dir);

	st->cfg.gpio_val = dib8000_read_word(st, 1030);
	st->cfg.gpio_val &= ~(1 << num);	/* reset the direction bit */
	st->cfg.gpio_val |= (val & 0x01) << num;	/* set the new value */
	dib8000_write_word(st, 1030, st->cfg.gpio_val);

	dprintk("gpio dir: %x: gpio val: %x\n", st->cfg.gpio_dir, st->cfg.gpio_val);

	return 0;
}