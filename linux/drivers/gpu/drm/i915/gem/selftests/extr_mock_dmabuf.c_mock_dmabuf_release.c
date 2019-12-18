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
struct mock_dmabuf {int npages; int /*<<< orphan*/ * pages; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mock_dmabuf*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 struct mock_dmabuf* to_mock (struct dma_buf*) ; 

__attribute__((used)) static void mock_dmabuf_release(struct dma_buf *dma_buf)
{
	struct mock_dmabuf *mock = to_mock(dma_buf);
	int i;

	for (i = 0; i < mock->npages; i++)
		put_page(mock->pages[i]);

	kfree(mock);
}