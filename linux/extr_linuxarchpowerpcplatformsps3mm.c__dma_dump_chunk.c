#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dma_chunk {int /*<<< orphan*/  len; int /*<<< orphan*/  bus_addr; int /*<<< orphan*/  lpar_addr; TYPE_2__* region; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  len; int /*<<< orphan*/  page_size; int /*<<< orphan*/  bus_addr; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  bus_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,char const*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void _dma_dump_chunk (const struct dma_chunk* c, const char* func,
	int line)
{
	DBG("%s:%d: r.dev        %llu:%llu\n", func, line,
		c->region->dev->bus_id, c->region->dev->dev_id);
	DBG("%s:%d: r.bus_addr   %lxh\n", func, line, c->region->bus_addr);
	DBG("%s:%d: r.page_size  %u\n", func, line, c->region->page_size);
	DBG("%s:%d: r.len        %lxh\n", func, line, c->region->len);
	DBG("%s:%d: r.offset     %lxh\n", func, line, c->region->offset);
	DBG("%s:%d: c.lpar_addr  %lxh\n", func, line, c->lpar_addr);
	DBG("%s:%d: c.bus_addr   %lxh\n", func, line, c->bus_addr);
	DBG("%s:%d: c.len        %lxh\n", func, line, c->len);
}