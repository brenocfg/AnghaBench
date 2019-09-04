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
struct alpine_msix_data {unsigned int spi_first; int /*<<< orphan*/  msi_map_lock; int /*<<< orphan*/  msi_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alpine_msix_free_sgi(struct alpine_msix_data *priv, unsigned sgi,
				 int num_req)
{
	int first = sgi - priv->spi_first;

	spin_lock(&priv->msi_map_lock);

	bitmap_clear(priv->msi_map, first, num_req);

	spin_unlock(&priv->msi_map_lock);
}