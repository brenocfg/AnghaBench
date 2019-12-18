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
struct io_pgtable_ops {int dummy; } ;
struct io_pgtable_init_fns {struct io_pgtable* (* alloc ) (struct io_pgtable_cfg*,void*) ;} ;
struct io_pgtable_cfg {int dummy; } ;
struct io_pgtable {int fmt; struct io_pgtable_ops ops; struct io_pgtable_cfg cfg; void* cookie; } ;
typedef  enum io_pgtable_fmt { ____Placeholder_io_pgtable_fmt } io_pgtable_fmt ;

/* Variables and functions */
 int IO_PGTABLE_NUM_FMTS ; 
 struct io_pgtable_init_fns** io_pgtable_init_table ; 
 struct io_pgtable* stub1 (struct io_pgtable_cfg*,void*) ; 

struct io_pgtable_ops *alloc_io_pgtable_ops(enum io_pgtable_fmt fmt,
					    struct io_pgtable_cfg *cfg,
					    void *cookie)
{
	struct io_pgtable *iop;
	const struct io_pgtable_init_fns *fns;

	if (fmt >= IO_PGTABLE_NUM_FMTS)
		return NULL;

	fns = io_pgtable_init_table[fmt];
	if (!fns)
		return NULL;

	iop = fns->alloc(cfg, cookie);
	if (!iop)
		return NULL;

	iop->fmt	= fmt;
	iop->cookie	= cookie;
	iop->cfg	= *cfg;

	return &iop->ops;
}