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
struct alpine_msix_data {int num_spis; int spi_first; int /*<<< orphan*/  msi_map_lock; int /*<<< orphan*/  msi_map; } ;

/* Variables and functions */
 int ENOSPC ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alpine_msix_allocate_sgi(struct alpine_msix_data *priv, int num_req)
{
	int first;

	spin_lock(&priv->msi_map_lock);

	first = bitmap_find_next_zero_area(priv->msi_map, priv->num_spis, 0,
					   num_req, 0);
	if (first >= priv->num_spis) {
		spin_unlock(&priv->msi_map_lock);
		return -ENOSPC;
	}

	bitmap_set(priv->msi_map, first, num_req);

	spin_unlock(&priv->msi_map_lock);

	return priv->spi_first + first;
}