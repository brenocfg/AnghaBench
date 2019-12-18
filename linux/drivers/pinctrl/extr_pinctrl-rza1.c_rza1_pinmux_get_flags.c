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
struct rza1_swio_entry {int dummy; } ;
struct rza1_pinmux_conf {struct rza1_swio_entry* swio_entries; struct rza1_bidir_entry* bidir_entries; } ;
struct rza1_pinctrl {struct rza1_pinmux_conf* data; } ;
struct rza1_bidir_entry {int dummy; } ;

/* Variables and functions */
 unsigned int MUX_FLAGS_BIDIR ; 
 unsigned int MUX_FLAGS_SWIO_INPUT ; 
 unsigned int MUX_FLAGS_SWIO_OUTPUT ; 
 scalar_t__ rza1_pinmux_get_bidir (unsigned int,unsigned int,unsigned int,struct rza1_bidir_entry const*) ; 
 int rza1_pinmux_get_swio (unsigned int,unsigned int,unsigned int,struct rza1_swio_entry const*) ; 

__attribute__((used)) static unsigned int rza1_pinmux_get_flags(unsigned int port, unsigned int pin,
					  unsigned int func,
					  struct rza1_pinctrl *rza1_pctl)

{
	const struct rza1_pinmux_conf *pmx_conf = rza1_pctl->data;
	const struct rza1_bidir_entry *bidir_entries = pmx_conf->bidir_entries;
	const struct rza1_swio_entry *swio_entries = pmx_conf->swio_entries;
	unsigned int pmx_flags = 0;
	int ret;

	if (rza1_pinmux_get_bidir(port, pin, func, bidir_entries))
		pmx_flags |= MUX_FLAGS_BIDIR;

	ret = rza1_pinmux_get_swio(port, pin, func, swio_entries);
	if (ret == 0)
		pmx_flags |= MUX_FLAGS_SWIO_OUTPUT;
	else if (ret > 0)
		pmx_flags |= MUX_FLAGS_SWIO_INPUT;

	return pmx_flags;
}