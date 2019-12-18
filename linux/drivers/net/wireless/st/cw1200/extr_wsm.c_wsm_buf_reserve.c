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
typedef  int /*<<< orphan*/  u8 ;
struct wsm_buf {int /*<<< orphan*/ * begin; int /*<<< orphan*/ * end; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FWLOAD_BLOCK_SIZE ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/ * krealloc (int /*<<< orphan*/ *,size_t,int) ; 
 size_t round_up (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_buf_deinit (struct wsm_buf*) ; 

__attribute__((used)) static int wsm_buf_reserve(struct wsm_buf *buf, size_t extra_size)
{
	size_t pos = buf->data - buf->begin;
	size_t size = pos + extra_size;
	u8 *tmp;

	size = round_up(size, FWLOAD_BLOCK_SIZE);

	tmp = krealloc(buf->begin, size, GFP_KERNEL | GFP_DMA);
	if (!tmp) {
		wsm_buf_deinit(buf);
		return -ENOMEM;
	}

	buf->begin = tmp;
	buf->data = &buf->begin[pos];
	buf->end = &buf->begin[size];
	return 0;
}