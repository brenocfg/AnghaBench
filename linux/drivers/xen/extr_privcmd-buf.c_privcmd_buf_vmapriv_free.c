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
struct privcmd_buf_vma_private {unsigned int n_pages; int /*<<< orphan*/ * pages; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct privcmd_buf_vma_private*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void privcmd_buf_vmapriv_free(struct privcmd_buf_vma_private *vma_priv)
{
	unsigned int i;

	list_del(&vma_priv->list);

	for (i = 0; i < vma_priv->n_pages; i++)
		__free_page(vma_priv->pages[i]);

	kfree(vma_priv);
}