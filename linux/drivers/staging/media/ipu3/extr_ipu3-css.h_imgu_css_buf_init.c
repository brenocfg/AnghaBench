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
struct imgu_css_buffer {unsigned int queue; int /*<<< orphan*/  daddr; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPU3_CSS_BUFFER_NEW ; 

__attribute__((used)) static inline void imgu_css_buf_init(struct imgu_css_buffer *b,
				     unsigned int queue, dma_addr_t daddr)
{
	b->state = IPU3_CSS_BUFFER_NEW;
	b->queue = queue;
	b->daddr = daddr;
}