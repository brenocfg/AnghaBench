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
typedef  int /*<<< orphan*/  uint ;
struct pkt_file {scalar_t__ buf_start; scalar_t__ cur_addr; scalar_t__ buf_len; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */

__attribute__((used)) static uint remainder_len(struct pkt_file *pfile)
{
	return (uint)(pfile->buf_len - ((addr_t)(pfile->cur_addr) -
	       (addr_t)(pfile->buf_start)));
}