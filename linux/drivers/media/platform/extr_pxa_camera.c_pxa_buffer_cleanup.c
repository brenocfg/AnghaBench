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
struct pxa_buffer {scalar_t__ nb_planes; scalar_t__* plane_sizes; scalar_t__* sg_len; int /*<<< orphan*/ ** sg; int /*<<< orphan*/ ** descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_desc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa_buffer_cleanup(struct pxa_buffer *buf)
{
	int i;

	for (i = 0; i < 3 && buf->descs[i]; i++) {
		dmaengine_desc_free(buf->descs[i]);
		kfree(buf->sg[i]);
		buf->descs[i] = NULL;
		buf->sg[i] = NULL;
		buf->sg_len[i] = 0;
		buf->plane_sizes[i] = 0;
	}
	buf->nb_planes = 0;
}