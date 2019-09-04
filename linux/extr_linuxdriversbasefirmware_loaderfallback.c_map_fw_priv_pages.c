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
struct fw_priv {int /*<<< orphan*/  data; int /*<<< orphan*/  nr_pages; int /*<<< orphan*/  pages; int /*<<< orphan*/  is_paged_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_KERNEL_RO ; 
 int /*<<< orphan*/  vmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_fw_priv_pages(struct fw_priv *fw_priv)
{
	if (!fw_priv->is_paged_buf)
		return 0;

	vunmap(fw_priv->data);
	fw_priv->data = vmap(fw_priv->pages, fw_priv->nr_pages, 0,
			     PAGE_KERNEL_RO);
	if (!fw_priv->data)
		return -ENOMEM;
	return 0;
}