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
struct gntdev_dmabuf_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmabuf_imp_release_all (struct gntdev_dmabuf_priv*) ; 
 int /*<<< orphan*/  kfree (struct gntdev_dmabuf_priv*) ; 

void gntdev_dmabuf_fini(struct gntdev_dmabuf_priv *priv)
{
	dmabuf_imp_release_all(priv);
	kfree(priv);
}