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
typedef  union ep_buffer_info {int dummy; } ep_buffer_info ;
typedef  int /*<<< orphan*/  u8 ;
struct epbuf_handler {int /*<<< orphan*/ * ring; union ep_buffer_info* info; int /*<<< orphan*/  size; void* buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EP_BUFFER_SIZE ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fjes_hw_alloc_epbuf(struct epbuf_handler *epbh)
{
	void *mem;

	mem = vzalloc(EP_BUFFER_SIZE);
	if (!mem)
		return -ENOMEM;

	epbh->buffer = mem;
	epbh->size = EP_BUFFER_SIZE;

	epbh->info = (union ep_buffer_info *)mem;
	epbh->ring = (u8 *)(mem + sizeof(union ep_buffer_info));

	return 0;
}