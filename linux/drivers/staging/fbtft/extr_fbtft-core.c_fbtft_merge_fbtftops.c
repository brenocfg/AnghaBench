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
struct fbtft_ops {scalar_t__ set_gamma; scalar_t__ set_var; scalar_t__ unregister_backlight; scalar_t__ register_backlight; scalar_t__ verify_gpios; scalar_t__ request_gpios; scalar_t__ request_gpios_match; scalar_t__ blank; scalar_t__ init_display; scalar_t__ update_display; scalar_t__ mkdirty; scalar_t__ reset; scalar_t__ set_addr_win; scalar_t__ write_register; scalar_t__ write_vmem; scalar_t__ read; scalar_t__ write; } ;

/* Variables and functions */

__attribute__((used)) static void fbtft_merge_fbtftops(struct fbtft_ops *dst, struct fbtft_ops *src)
{
	if (src->write)
		dst->write = src->write;
	if (src->read)
		dst->read = src->read;
	if (src->write_vmem)
		dst->write_vmem = src->write_vmem;
	if (src->write_register)
		dst->write_register = src->write_register;
	if (src->set_addr_win)
		dst->set_addr_win = src->set_addr_win;
	if (src->reset)
		dst->reset = src->reset;
	if (src->mkdirty)
		dst->mkdirty = src->mkdirty;
	if (src->update_display)
		dst->update_display = src->update_display;
	if (src->init_display)
		dst->init_display = src->init_display;
	if (src->blank)
		dst->blank = src->blank;
	if (src->request_gpios_match)
		dst->request_gpios_match = src->request_gpios_match;
	if (src->request_gpios)
		dst->request_gpios = src->request_gpios;
	if (src->verify_gpios)
		dst->verify_gpios = src->verify_gpios;
	if (src->register_backlight)
		dst->register_backlight = src->register_backlight;
	if (src->unregister_backlight)
		dst->unregister_backlight = src->unregister_backlight;
	if (src->set_var)
		dst->set_var = src->set_var;
	if (src->set_gamma)
		dst->set_gamma = src->set_gamma;
}